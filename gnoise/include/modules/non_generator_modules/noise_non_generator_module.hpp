#pragma once

#include "../noise_module.hpp"

GNOISE_NAMESPACE_BEGIN

namespace non_generator_utility
{
    template<class MT, class ItOut, class P, class... It>
    void element_wise_transform(const MT* module, ItOut b, ItOut e, P predicate, It... bs)
    {
        while (b != e)
        {
            *(b++) = predicate(module, *(bs++)...);
        }
    }

    template<class MT, class ItOut, class P, size_t MS_C, size_t...  I>
    void expand_array_to_ew_transform(const MT* module, ItOut b, ItOut e, P predicate, const array<vector<float>::const_iterator, MS_C>& arr, std::index_sequence<I...>)
    {
        element_wise_transform(module, b, e, predicate, arr[I]...);
    }

    template<unsigned int D, class MT, class P, class... MS>
    inline vector<float> non_generator_value_points_stcpu_impl(const MT* module, const vector<vectorf<D>>& points, P predicate, const MS*... modules)
    {
        array<vector<float>, sizeof...(MS)> values = { modules->compute(points)... };

        if (std::any_of(values.begin(), values.end(), [](const vector<float>& v) {
            return v.empty();
        }))
        {
            return vector<float>();
        }

        if (std::any_of(values.begin(), values.end(), [&values](const vector<float>& v) {
            return v.size() != values.front().size();
        }))
        {
            return vector<float>();
        }

        array<vector<float>::const_iterator, sizeof...(MS)> values_iterators;
        std::transform(values.begin(), values.end(), values_iterators.begin(), [](const vector<float>& v) {
            return v.begin();
        });

        expand_array_to_ew_transform(module, values.front().begin(), values.front().end(), predicate, values_iterators, std::index_sequence_for<MS...>());

        return values.front();
    }

    template<unsigned int D, class MT, class P, class... MS>
    inline vector<float> non_generator_value_points_mtcpu_impl(const MT* module, const vector<vectorf<D>>& points, P predicate, const MS*... modules)
    {
        float affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

        auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
        if (cores_assigned == 0)
        {
            return vector<float>();
        }

        array<vector<float>, sizeof...(MS)> values = { modules->compute(points)... };

        if (std::any_of(values.begin(), values.end(), [](const vector<float>& v) {
            return v.empty();
        }))
        {
            return vector<float>();
        }

        if (std::any_of(values.begin(), values.end(), [&values](const vector<float>& v) {
            return v.size() != values.front().size();
        }))
        {
            return vector<float>();
        }

        array<vector<float>::const_iterator, sizeof...(MS)> values_iterators;
        std::transform(values.begin(), values.end(), values_iterators.begin(), [](const vector<float>& v) {
            return v.begin();
        });

        vector<std::thread> work_threads(cores_assigned);
        auto div = static_cast<float>(points.size()) / cores_assigned;
        for (size_t i = 0; i < work_threads.size(); i++)
        {
            array<vector<float>::const_iterator, sizeof...(MS)> thread_start_its;
            std::transform(values_iterators.begin(), values_iterators.end(), thread_start_its.begin(), [&div, &i](const vector<float>::const_iterator& v) {
                return v + static_cast<size_t>(div * i);
            });
            auto thread_start_values_it = values.front().begin() + static_cast<size_t>(div * i);
            auto thread_end_values_it = values.front().begin() + static_cast<size_t>(div * (i + 1));

            work_threads[i] = std::thread([thread_start_its, thread_start_values_it, thread_end_values_it, &predicate, &module]() {
                expand_array_to_ew_transform(module, thread_start_values_it, thread_end_values_it, predicate, thread_start_its, std::index_sequence_for<MS...>());
            });
        }

        for (auto& thread : work_threads)
        {
            thread.join();
        }

        return values.front();
    }

    template<unsigned int D, class MT, class P, class... MS>
    inline vector<float> non_generator_value_range_stcpu_impl(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate, const MS*... modules)
    {
        array<vector<float>, sizeof...(MS)> values = { modules->compute(range, precision)... };

        if (std::any_of(values.begin(), values.end(), [](const vector<float>& v) {
            return v.empty();
        }))
        {
            return vector<float>();
        }

        if (std::any_of(values.begin(), values.end(), [&values](const vector<float>& v) {
            return v.size() != values.front().size();
        }))
        {
            return vector<float>();
        }

        array<vector<float>::const_iterator, sizeof...(MS)> values_iterators;
        std::transform(values.begin(), values.end(), values_iterators.begin(), [](const vector<float>& v) {
            return v.begin();
        });

        expand_array_to_ew_transform(module, values.front().begin(), values.front().end(), predicate, values_iterators, std::index_sequence_for<MS...>());

        return values.front();
    }

    template<unsigned int D, class MT, class P, class... MS>
    inline vector<float> non_generator_value_range_mtcpu_impl(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate, const MS*... modules)
    {
        float affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

        auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
        if (cores_assigned == 0)
        {
            return vector<float>();
        }

        array<vector<float>, sizeof...(MS)> values = { modules->compute(range, precision)... };

        if (std::any_of(values.begin(), values.end(), [](const vector<float>& v) {
            return v.empty();
        }))
        {
            return vector<float>();
        }

        if (std::any_of(values.begin(), values.end(), [&values](const vector<float>& v) {
            return v.size() != values.front().size();
        }))
        {
            return vector<float>();
        }

        array<vector<float>::const_iterator, sizeof...(MS)> values_iterators;
        std::transform(values.begin(), values.end(), values_iterators.begin(), [](const vector<float>& v) {
            return v.begin();
        });

        vector<std::thread> work_threads(cores_assigned);
        auto div = static_cast<float>(values.front().size()) / cores_assigned;
        for (size_t i = 0; i < work_threads.size(); i++)
        {
            array<vector<float>::const_iterator, sizeof...(MS)> thread_start_its;
            std::transform(values_iterators.begin(), values_iterators.end(), thread_start_its.begin(), [&div, &i](const vector<float>::const_iterator& v) {
                return v + static_cast<size_t>(div * i);
            });
            auto thread_start_values_it = values.front().begin() + static_cast<size_t>(div * i);
            auto thread_end_values_it = values.front().begin() + static_cast<size_t>(div * (i + 1));

            work_threads[i] = std::thread([thread_start_its, thread_start_values_it, thread_end_values_it, &predicate, &module]() {
                expand_array_to_ew_transform(module, thread_start_values_it, thread_end_values_it, predicate, thread_start_its, std::index_sequence_for<MS...>());
            });
        }

        for (auto& thread : work_threads)
        {
            thread.join();
        }

        return values.front();
    }

    template<unsigned int D, class MT, class P, size_t... I>
    inline float non_generator_value(const MT* module, const vectorf<D>& point, P predicate, std::index_sequence<I...>)
    {
        return predicate(module, module->input_module(I)->compute(point)...);
    }

    template<unsigned int D, class MT, class P, size_t... I>
    inline vector<float> non_generator_value_points_stcpu(const MT* module, const vector<vectorf<D>>& points, P predicate, std::index_sequence<I...>)
    {
        return non_generator_utility::non_generator_value_points_stcpu_impl(module, points, predicate, module->input_module(I)...);
    }

    template<unsigned int D, class MT, class P, size_t... I>
    inline vector<float> non_generator_value_points_mtcpu(const MT* module, const vector<vectorf<D>>& points, P predicate, std::index_sequence<I...>)
    {
        return non_generator_utility::non_generator_value_points_mtcpu_impl(module, points, predicate, module->input_module(I)...);
    }

    template<unsigned int D, class MT, class P, size_t... I>
    inline vector<float> non_generator_value_range_stcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate, std::index_sequence<I...>)
    {
        return non_generator_utility::non_generator_value_range_stcpu_impl(module, range, precision, predicate, module->input_module(I)...);
    }

    template<unsigned int D, class MT, class P, size_t... I>
    inline vector<float> non_generator_value_range_mtcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate, std::index_sequence<I...>)
    {
        return non_generator_utility::non_generator_value_range_mtcpu_impl(module, range, precision, predicate, module->input_module(I)...);
    }
}

class noise_non_generator_module_base : public noise_module
{
protected:
    noise_non_generator_module_base() noexcept = default;
public:
    noise_non_generator_module_base(const noise_non_generator_module_base&) = delete;
    noise_non_generator_module_base(noise_non_generator_module_base&&) = delete;
    noise_non_generator_module_base& operator=(const noise_non_generator_module_base&) = delete;
    noise_non_generator_module_base& operator=(noise_non_generator_module_base&&) = delete;
public:
    virtual size_t                                  input_modules_count() const = 0;
    virtual vector<const noise_module*>             input_modules() const = 0;
    virtual const noise_module*                     input_module(size_t index) const = 0;
    
    virtual bool                                    set_input_module(size_t index, const noise_module* module) = 0;
protected:
    virtual void                                    on_configuration_changed() override;
};

template<size_t I_C>
class noise_non_generator_module_def_impl_base : public noise_non_generator_module_base
{
protected:
    noise_non_generator_module_def_impl_base() noexcept:
        noise_non_generator_module_base()
    {
        std::fill(_input_modules.begin(), _input_modules.end(), nullptr);
    }
public:
    noise_non_generator_module_def_impl_base(const noise_non_generator_module_def_impl_base&) = delete;
    noise_non_generator_module_def_impl_base(noise_non_generator_module_def_impl_base&&) = delete;
    noise_non_generator_module_def_impl_base& operator=(const noise_non_generator_module_def_impl_base&) = delete;
    noise_non_generator_module_def_impl_base& operator=(noise_non_generator_module_def_impl_base&&) = delete;
public:
    virtual size_t                                  input_modules_count() const override
    {
        return I_C;
    }
    virtual vector<const noise_module*>             input_modules() const override
    {
        vector<const noise_module*> cp(I_C);
        std::copy(_input_modules.begin(), _input_modules.end(), cp.begin());
        return cp;
    }
    virtual const noise_module*                     input_module(size_t index) const override
    {
        if(index >= I_C)
        {
            return nullptr;
        }
        return _input_modules[index];
    }

    virtual bool                                    set_input_module(size_t index, const noise_module* module) override
    {
        if (index >= I_C || !module)
        {
            return false;
        }
        _input_modules[index] = module;
        return true;
    }
protected:
    array<const noise_module*, I_C>                 _input_modules;
};

template<>
class noise_non_generator_module_def_impl_base<0> : public noise_non_generator_module_base
{
protected:
    noise_non_generator_module_def_impl_base() noexcept = default;
public:
    noise_non_generator_module_def_impl_base(const noise_non_generator_module_def_impl_base&) = delete;
    noise_non_generator_module_def_impl_base(noise_non_generator_module_def_impl_base&&) = delete;
    noise_non_generator_module_def_impl_base& operator=(const noise_non_generator_module_def_impl_base&) = delete;
    noise_non_generator_module_def_impl_base& operator=(noise_non_generator_module_def_impl_base&&) = delete;
public:
    virtual size_t                                  input_modules_count() const override
    {
        return 0;
    }
    virtual vector<const noise_module*>             input_modules() const override
    {
        return vector<const noise_module*>();
    }
    virtual const noise_module*                     input_module(size_t index) const override
    {
        return nullptr;
    }

    virtual bool                                    set_input_module(size_t index, const noise_module* module) override
    {
        return false;
    }
};

template<size_t I_C, class F, class D, module_type MT>
class noise_non_generator_module_def_impl : public noise_non_generator_module_def_impl_base<I_C>
{
public:
    noise_non_generator_module_def_impl() noexcept = default;
public:
    virtual gnoise::module_type                     module_type() const override
    {
        return MT;
    }

    virtual float                                   compute(const vector1f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;

        }
        return non_generator_utility::non_generator_value(reinterpret_cast<const D*>(this), point, F::apply, std::make_index_sequence<I_C>());
    }
    virtual float                                   compute(const vector2f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;

        }
        return non_generator_utility::non_generator_value(reinterpret_cast<const D*>(this), point, F::apply, std::make_index_sequence<I_C>());
    }
    virtual float                                   compute(const vector3f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;

        }
        return non_generator_utility::non_generator_value(reinterpret_cast<const D*>(this), point, F::apply, std::make_index_sequence<I_C>());
    }
    virtual float                                   compute(const vector4f& point) const override
    {
        if (!check_input_modules_validity())
        {
            return 0.0f;

        }
        return non_generator_utility::non_generator_value(reinterpret_cast<const D*>(this), point, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_points_stcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
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
            return non_generator_utility::non_generator_value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        case module_computation_target::open_cl:
        case module_computation_target::multi_thread_cpu:
        {
            return non_generator_utility::non_generator_value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::apply, std::make_index_sequence<I_C>());
        }
        break;
        }

        return vector<float>();
    }
protected:
    virtual void                                    on_configuration_changed() override
    {
        if (configuration().computation_target() == module_computation_target::gpu)
        {
            configuration().set_computation_target(module_computation_target::mtcpu);
        }
    }
private:
    bool                                            check_input_modules_validity() const
    {
        auto modules = input_modules();
        return std::all_of(modules.begin(), modules.end(), [](const auto& v) {
            return v != nullptr;
        });
    }
};

GNOISE_NAMESPACE_END
