#pragma once

#include "../noise_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

namespace linear_transformer_utility
{
    template<class MT, unsigned int D, class P>
    inline float linear_transformer_value_point(const MT* module, vectorf<D> point, P predicate)
    {
        predicate(module, point);
        return module->input_module(0)->compute(point);
    }

    template<class MT, unsigned int D, class P>
    inline vector<float> linear_transformer_value_points_stcpu(const MT* module, vector<vectorf<D>> points, P predicate)
    {
        std::for_each(points.begin(), points.end(), [&module, &predicate](vectorf<D>& point) {
            predicate(module, point);
        });

        return module->input_module(0)->compute(points);
    }

    template<class MT, unsigned int D, class P>
    inline vector<float> linear_transformer_value_points_mtcpu(const MT* module, vector<vectorf<D>> points, P predicate)
    {
        float affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

        auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
        if (cores_assigned == 0)
        {
            return vector<float>();
        }

        vector<std::thread> work_threads(cores_assigned);
        auto div = static_cast<float>(points.size()) / cores_assigned;
        for (size_t i = 0; i < work_threads.size(); i++)
        {
            auto thread_start_it = points.begin() + static_cast<size_t>(div * i);
            auto thread_end_it = points.begin() + static_cast<size_t>(div * (i + 1));

            work_threads[i] = std::thread([thread_start_it, thread_end_it, &module, &points, &predicate]() {
                std::for_each(thread_start_it, thread_end_it, [&module, &predicate](vectorf<D>& point) {
                    predicate(module, point);
                });
            });
        }

        for (auto& thread : work_threads)
        {
            thread.join();
        }

        return module->input_module(0)->compute(points);
    }

    template<class MT, unsigned int D, class P>
    inline vector<float> linear_transformer_value_range_stcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate)
    {
        unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());

        vector<vectorf<D>> points(precision_all_dim);

        for (unsigned long long int i = 0; i < precision_all_dim; i++)
        {
            array<unsigned long long int, D> coord_prec;

            unsigned long long int curr_div = 1;

            for (size_t j = 0; j < D; j++)
            {
                coord_prec[j] = (i / curr_div) % precision[j];
                curr_div *= precision[j];
            }

            vectorf<D> coords;

            for (size_t j = 0; j < D; j++)
            {
                coords.coords[j] = coord_prec[j] / static_cast<float>(precision[j]);
            }

            points[i] = coords;
        }

        return linear_transformer_value_points_stcpu(module, points, predicate);
    }

    template<class MT, unsigned int D, class P>
    inline vector<float> linear_transformer_value_range_mtcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate)
    {
        unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());

        vector<vectorf<D>> points(precision_all_dim);

        for (unsigned long long int i = 0; i < precision_all_dim; i++)
        {
            array<unsigned long long int, D> coord_prec;

            unsigned long long int curr_div = 1;

            for (size_t j = 0; j < D; j++)
            {
                coord_prec[j] = (i / curr_div) % precision[j];
                curr_div *= precision[j];
            }

            vectorf<D> coords;

            for (size_t j = 0; j < D; j++)
            {
                coords.coords[j] = coord_prec[j] / static_cast<float>(precision[j]);
            }

            points[i] = coords;
        }

        return linear_transformer_value_points_mtcpu(module, points, predicate);
    }
}

template<class F, class D>
class noise_linear_transformer_module_base_def_impl : public noise_transformer_module_base<1>
{
public:
    noise_linear_transformer_module_base_def_impl() noexcept = default;
public:
    virtual float                                   compute(const vector1f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;
        }
        return linear_transformer_utility::linear_transformer_value_point(reinterpret_cast<const D*>(this), point, F::transform<1>);
    }
    virtual float                                   compute(const vector2f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;
        }
        return linear_transformer_utility::linear_transformer_value_point(reinterpret_cast<const D*>(this), point, F::transform<2>);
    }
    virtual float                                   compute(const vector3f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;
        }
        return linear_transformer_utility::linear_transformer_value_point(reinterpret_cast<const D*>(this), point, F::transform<3>);
    }
    virtual float                                   compute(const vector4f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;
        }
        return linear_transformer_utility::linear_transformer_value_point(reinterpret_cast<const D*>(this), point, F::transform<4>);
    }

    virtual vector<float>                           compute(const vector<vector1f>& points) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::transform<1>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::transform<1>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector2f>& points) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::transform<2>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::transform<2>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector3f>& points) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::transform<3>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::transform<3>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector4f>& points) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::transform<4>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::transform<4>);
        }
        break;
        }

        return vector<float>();
    }

    virtual vector<float>                           compute(const range1f& range, const precision1& precision) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<1>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<1>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range2f& range, const precision2& precision) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<2>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<2>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range3f& range, const precision3& precision) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<3>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<3>);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range4f& range, const precision4& precision) const override
    {
        if (!check_input_modules_validity())
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<4>);
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return linear_transformer_utility::linear_transformer_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::transform<4>);
        }
        break;
        }

        return vector<float>();
    }
private:
    bool                                            check_input_modules_validity() const
    {
        return input_module(0) != nullptr;
    }
};

GNOISE_NAMESPACE_END