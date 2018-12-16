#pragma once

#include "../noise_module.hpp"

GNOISE_NAMESPACE_BEGIN

enum noise_quality
{
    fast,
    standard,
    best
};

inline constexpr unsigned int maximum_octave_count = 64;

namespace generator_utility
{
    inline constexpr array<float, 1024> randoms = {
        -0.763874f, -0.596439f, -0.246489f, 0.0f, 0.396055f, 0.904518f, -0.158073f, 0.0f,
        -0.499004f, -0.8665f, -0.0131631f, 0.0f, 0.468724f, -0.824756f, 0.316346f, 0.0f,
        0.829598f, 0.43195f, 0.353816f, 0.0f, -0.454473f, 0.629497f, -0.630228f, 0.0f,
        -0.162349f, -0.869962f, -0.465628f, 0.0f, 0.932805f, 0.253451f, 0.256198f, 0.0f,
        -0.345419f, 0.927299f, -0.144227f, 0.0f, -0.715026f, -0.293698f, -0.634413f, 0.0f,
        -0.245997f, 0.717467f, -0.651711f, 0.0f, -0.967409f, -0.250435f, -0.037451f, 0.0f,
        0.901729f, 0.397108f, -0.170852f, 0.0f, 0.892657f, -0.0720622f, -0.444938f, 0.0f,
        0.0260084f, -0.0361701f, 0.999007f, 0.0f, 0.949107f, -0.19486f, 0.247439f, 0.0f,
        0.471803f, -0.807064f, -0.355036f, 0.0f, 0.879737f, 0.141845f, 0.453809f, 0.0f,
        0.570747f, 0.696415f, 0.435033f, 0.0f, -0.141751f, -0.988233f, -0.0574584f, 0.0f,
        -0.58219f, -0.0303005f, 0.812488f, 0.0f, -0.60922f, 0.239482f, -0.755975f, 0.0f,
        0.299394f, -0.197066f, -0.933557f, 0.0f, -0.851615f, -0.220702f, -0.47544f, 0.0f,
        0.848886f, 0.341829f, -0.403169f, 0.0f, -0.156129f, -0.687241f, 0.709453f, 0.0f,
        -0.665651f, 0.626724f, 0.405124f, 0.0f, 0.595914f, -0.674582f, 0.43569f, 0.0f,
        0.171025f, -0.509292f, 0.843428f, 0.0f, 0.78605f, 0.536414f, -0.307222f, 0.0f,
        0.18905f, -0.791613f, 0.581042f, 0.0f, -0.294916f, 0.844994f, 0.446105f, 0.0f,
        0.342031f, -0.58736f, -0.7335f, 0.0f, 0.57155f, 0.7869f, 0.232635f, 0.0f,
        0.885026f, -0.408223f, 0.223791f, 0.0f, -0.789518f, 0.571645f, 0.223347f, 0.0f,
        0.774571f, 0.31566f, 0.548087f, 0.0f, -0.79695f, -0.0433603f, -0.602487f, 0.0f,
        -0.142425f, -0.473249f, -0.869339f, 0.0f, -0.0698838f, 0.170442f, 0.982886f, 0.0f,
        0.687815f, -0.484748f, 0.540306f, 0.0f, 0.543703f, -0.534446f, -0.647112f, 0.0f,
        0.97186f, 0.184391f, -0.146588f, 0.0f, 0.707084f, 0.485713f, -0.513921f, 0.0f,
        0.942302f, 0.331945f, 0.043348f, 0.0f, 0.499084f, 0.599922f, 0.625307f, 0.0f,
        -0.289203f, 0.211107f, 0.9337f, 0.0f, 0.412433f, -0.71667f, -0.56239f, 0.0f,
        0.87721f, -0.082816f, 0.47291f, 0.0f, -0.420685f, -0.214278f, 0.881538f, 0.0f,
        0.752558f, -0.0391579f, 0.657361f, 0.0f, 0.0765725f, -0.996789f, 0.0234082f, 0.0f,
        -0.544312f, -0.309435f, -0.779727f, 0.0f, -0.455358f, -0.415572f, 0.787368f, 0.0f,
        -0.874586f, 0.483746f, 0.0330131f, 0.0f, 0.245172f, -0.0838623f, 0.965846f, 0.0f,
        0.382293f, -0.432813f, 0.81641f, 0.0f, -0.287735f, -0.905514f, 0.311853f, 0.0f,
        -0.667704f, 0.704955f, -0.239186f, 0.0f, 0.717885f, -0.464002f, -0.518983f, 0.0f,
        0.976342f, -0.214895f, 0.0240053f, 0.0f, -0.0733096f, -0.921136f, 0.382276f, 0.0f,
        -0.986284f, 0.151224f, -0.0661379f, 0.0f, -0.899319f, -0.429671f, 0.0812908f, 0.0f,
        0.652102f, -0.724625f, 0.222893f, 0.0f, 0.203761f, 0.458023f, -0.865272f, 0.0f,
        -0.030396f, 0.698724f, -0.714745f, 0.0f, -0.460232f, 0.839138f, 0.289887f, 0.0f,
        -0.0898602f, 0.837894f, 0.538386f, 0.0f, -0.731595f, 0.0793784f, 0.677102f, 0.0f,
        -0.447236f, -0.788397f, 0.422386f, 0.0f, 0.186481f, 0.645855f, -0.740335f, 0.0f,
        -0.259006f, 0.935463f, 0.240467f, 0.0f, 0.445839f, 0.819655f, -0.359712f, 0.0f,
        0.349962f, 0.755022f, -0.554499f, 0.0f, -0.997078f, -0.0359577f, 0.0673977f, 0.0f,
        -0.431163f, -0.147516f, -0.890133f, 0.0f, 0.299648f, -0.63914f, 0.708316f, 0.0f,
        0.397043f, 0.566526f, -0.722084f, 0.0f, -0.502489f, 0.438308f, -0.745246f, 0.0f,
        0.0687235f, 0.354097f, 0.93268f, 0.0f, -0.0476651f, -0.462597f, 0.885286f, 0.0f,
        -0.221934f, 0.900739f, -0.373383f, 0.0f, -0.956107f, -0.225676f, 0.186893f, 0.0f,
        -0.187627f, 0.391487f, -0.900852f, 0.0f, -0.224209f, -0.315405f, 0.92209f, 0.0f,
        -0.730807f, -0.537068f, 0.421283f, 0.0f, -0.0353135f, -0.816748f, 0.575913f, 0.0f,
        -0.941391f, 0.176991f, -0.287153f, 0.0f, -0.154174f, 0.390458f, 0.90762f, 0.0f,
        -0.283847f, 0.533842f, 0.796519f, 0.0f, -0.482737f, -0.850448f, 0.209052f, 0.0f,
        -0.649175f, 0.477748f, 0.591886f, 0.0f, 0.885373f, -0.405387f, -0.227543f, 0.0f,
        -0.147261f, 0.181623f, -0.972279f, 0.0f, 0.0959236f, -0.115847f, -0.988624f, 0.0f,
        -0.89724f, -0.191348f, 0.397928f, 0.0f, 0.903553f, -0.428461f, -0.00350461f, 0.0f,
        0.849072f, -0.295807f, -0.437693f, 0.0f, 0.65551f, 0.741754f, -0.141804f, 0.0f,
        0.61598f, -0.178669f, 0.767232f, 0.0f, 0.0112967f, 0.932256f, -0.361623f, 0.0f,
        -0.793031f, 0.258012f, 0.551845f, 0.0f, 0.421933f, 0.454311f, 0.784585f, 0.0f,
        -0.319993f, 0.0401618f, -0.946568f, 0.0f, -0.81571f, 0.551307f, -0.175151f, 0.0f,
        -0.377644f, 0.00322313f, 0.925945f, 0.0f, 0.129759f, -0.666581f, -0.734052f, 0.0f,
        0.601901f, -0.654237f, -0.457919f, 0.0f, -0.927463f, -0.0343576f, -0.372334f, 0.0f,
        -0.438663f, -0.868301f, -0.231578f, 0.0f, -0.648845f, -0.749138f, -0.133387f, 0.0f,
        0.507393f, -0.588294f, 0.629653f, 0.0f, 0.726958f, 0.623665f, 0.287358f, 0.0f,
        0.411159f, 0.367614f, -0.834151f, 0.0f, 0.806333f, 0.585117f, -0.0864016f, 0.0f,
        0.263935f, -0.880876f, 0.392932f, 0.0f, 0.421546f, -0.201336f, 0.884174f, 0.0f,
        -0.683198f, -0.569557f, -0.456996f, 0.0f, -0.117116f, -0.0406654f, -0.992285f, 0.0f,
        -0.643679f, -0.109196f, -0.757465f, 0.0f, -0.561559f, -0.62989f, 0.536554f, 0.0f,
        0.0628422f, 0.104677f, -0.992519f, 0.0f, 0.480759f, -0.2867f, -0.828658f, 0.0f,
        -0.228559f, -0.228965f, -0.946222f, 0.0f, -0.10194f, -0.65706f, -0.746914f, 0.0f,
        0.0689193f, -0.678236f, 0.731605f, 0.0f, 0.401019f, -0.754026f, 0.52022f, 0.0f,
        -0.742141f, 0.547083f, -0.387203f, 0.0f, -0.00210603f, -0.796417f, -0.604745f, 0.0f,
        0.296725f, -0.409909f, -0.862513f, 0.0f, -0.260932f, -0.798201f, 0.542945f, 0.0f,
        -0.641628f, 0.742379f, 0.192838f, 0.0f, -0.186009f, -0.101514f, 0.97729f, 0.0f,
        0.106711f, -0.962067f, 0.251079f, 0.0f, -0.743499f, 0.30988f, -0.592607f, 0.0f,
        -0.795853f, -0.605066f, -0.0226607f, 0.0f, -0.828661f, -0.419471f, -0.370628f, 0.0f,
        0.0847218f, -0.489815f, -0.8677f, 0.0f, -0.381405f, 0.788019f, -0.483276f, 0.0f,
        0.282042f, -0.953394f, 0.107205f, 0.0f, 0.530774f, 0.847413f, 0.0130696f, 0.0f,
        0.0515397f, 0.922524f, 0.382484f, 0.0f, -0.631467f, -0.709046f, 0.313852f, 0.0f,
        0.688248f, 0.517273f, 0.508668f, 0.0f, 0.646689f, -0.333782f, -0.685845f, 0.0f,
        -0.932528f, -0.247532f, -0.262906f, 0.0f, 0.630609f, 0.68757f, -0.359973f, 0.0f,
        0.577805f, -0.394189f, 0.714673f, 0.0f, -0.887833f, -0.437301f, -0.14325f, 0.0f,
        0.690982f, 0.174003f, 0.701617f, 0.0f, -0.866701f, 0.0118182f, 0.498689f, 0.0f,
        -0.482876f, 0.727143f, 0.487949f, 0.0f, -0.577567f, 0.682593f, -0.447752f, 0.0f,
        0.373768f, 0.0982991f, 0.922299f, 0.0f, 0.170744f, 0.964243f, -0.202687f, 0.0f,
        0.993654f, -0.035791f, -0.106632f, 0.0f, 0.587065f, 0.4143f, -0.695493f, 0.0f,
        -0.396509f, 0.26509f, -0.878924f, 0.0f, -0.0866853f, 0.83553f, -0.542563f, 0.0f,
        0.923193f, 0.133398f, -0.360443f, 0.0f, 0.00379108f, -0.258618f, 0.965972f, 0.0f,
        0.239144f, 0.245154f, -0.939526f, 0.0f, 0.758731f, -0.555871f, 0.33961f, 0.0f,
        0.295355f, 0.309513f, 0.903862f, 0.0f, 0.0531222f, -0.91003f, -0.411124f, 0.0f,
        0.270452f, 0.0229439f, -0.96246f, 0.0f, 0.563634f, 0.0324352f, 0.825387f, 0.0f,
        0.156326f, 0.147392f, 0.976646f, 0.0f, -0.0410141f, 0.981824f, 0.185309f, 0.0f,
        -0.385562f, -0.576343f, -0.720535f, 0.0f, 0.388281f, 0.904441f, 0.176702f, 0.0f,
        0.945561f, -0.192859f, -0.262146f, 0.0f, 0.844504f, 0.520193f, 0.127325f, 0.0f,
        0.0330893f, 0.999121f, -0.0257505f, 0.0f, -0.592616f, -0.482475f, -0.644999f, 0.0f,
        0.539471f, 0.631024f, -0.557476f, 0.0f, 0.655851f, -0.027319f, -0.754396f, 0.0f,
        0.274465f, 0.887659f, 0.369772f, 0.0f, -0.123419f, 0.975177f, -0.183842f, 0.0f,
        -0.223429f, 0.708045f, 0.66989f, 0.0f, -0.908654f, 0.196302f, 0.368528f, 0.0f,
        -0.95759f, -0.00863708f, 0.288005f, 0.0f, 0.960535f, 0.030592f, 0.276472f, 0.0f,
        -0.413146f, 0.907537f, 0.0754161f, 0.0f, -0.847992f, 0.350849f, -0.397259f, 0.0f,
        0.614736f, 0.395841f, 0.68221f, 0.0f, -0.503504f, -0.666128f, -0.550234f, 0.0f,
        -0.268833f, -0.738524f, -0.618314f, 0.0f, 0.792737f, -0.60001f, -0.107502f, 0.0f,
        -0.637582f, 0.508144f, -0.579032f, 0.0f, 0.750105f, 0.282165f, -0.598101f, 0.0f,
        -0.351199f, -0.392294f, -0.850155f, 0.0f, 0.250126f, -0.960993f, -0.118025f, 0.0f,
        -0.732341f, 0.680909f, -0.0063274f, 0.0f, -0.760674f, -0.141009f, 0.633634f, 0.0f,
        0.222823f, -0.304012f, 0.926243f, 0.0f, 0.209178f, 0.505671f, 0.836984f, 0.0f,
        0.757914f, -0.56629f, -0.323857f, 0.0f, -0.782926f, -0.339196f, 0.52151f, 0.0f,
        -0.462952f, 0.585565f, 0.665424f, 0.0f, 0.61879f, 0.194119f, -0.761194f, 0.0f,
        0.741388f, -0.276743f, 0.611357f, 0.0f, 0.707571f, 0.702621f, 0.0752872f, 0.0f,
        0.156562f, 0.819977f, 0.550569f, 0.0f, -0.793606f, 0.440216f, 0.42f, 0.0f,
        0.234547f, 0.885309f, -0.401517f, 0.0f, 0.132598f, 0.80115f, -0.58359f, 0.0f,
        -0.377899f, -0.639179f, 0.669808f, 0.0f, -0.865993f, -0.396465f, 0.304748f, 0.0f,
        -0.624815f, -0.44283f, 0.643046f, 0.0f, -0.485705f, 0.825614f, -0.287146f, 0.0f,
        -0.971788f, 0.175535f, 0.157529f, 0.0f, -0.456027f, 0.392629f, 0.798675f, 0.0f,
        -0.0104443f, 0.521623f, -0.853112f, 0.0f, -0.660575f, -0.74519f, 0.091282f, 0.0f,
        -0.0157698f, -0.307475f, -0.951425f, 0.0f, -0.603467f, -0.250192f, 0.757121f, 0.0f,
        0.506876f, 0.25006f, 0.824952f, 0.0f, 0.255404f, 0.966794f, 0.00884498f, 0.0f,
        0.466764f, -0.874228f, -0.133625f, 0.0f, 0.475077f, -0.0682351f, -0.877295f, 0.0f,
        -0.224967f, -0.938972f, -0.260233f, 0.0f, -0.377929f, -0.814757f, -0.439705f, 0.0f,
        -0.305847f, 0.542333f, -0.782517f, 0.0f, 0.26658f, -0.902905f, -0.337191f, 0.0f,
        0.0275773f, 0.322158f, -0.946284f, 0.0f, 0.0185422f, 0.716349f, 0.697496f, 0.0f,
        -0.20483f, 0.978416f, 0.0273371f, 0.0f, -0.898276f, 0.373969f, 0.230752f, 0.0f,
        -0.00909378f, 0.546594f, 0.837349f, 0.0f, 0.6602f, -0.751089f, 0.000959236f, 0.0f,
        0.855301f, -0.303056f, 0.420259f, 0.0f, 0.797138f, 0.0623013f, -0.600574f, 0.0f,
        0.48947f, -0.866813f, 0.0951509f, 0.0f, 0.251142f, 0.674531f, 0.694216f, 0.0f,
        -0.578422f, -0.737373f, -0.348867f, 0.0f, -0.254689f, -0.514807f, 0.818601f, 0.0f,
        0.374972f, 0.761612f, 0.528529f, 0.0f, 0.640303f, -0.734271f, -0.225517f, 0.0f,
        -0.638076f, 0.285527f, 0.715075f, 0.0f, 0.772956f, -0.15984f, -0.613995f, 0.0f,
        0.798217f, -0.590628f, 0.118356f, 0.0f, -0.986276f, -0.0578337f, -0.154644f, 0.0f,
        -0.312988f, -0.94549f, 0.0899272f, 0.0f, -0.497338f, 0.178325f, 0.849032f, 0.0f,
        -0.101136f, -0.981014f, 0.165477f, 0.0f, -0.521688f, 0.0553434f, -0.851339f, 0.0f,
        -0.786182f, -0.583814f, 0.202678f, 0.0f, -0.565191f, 0.821858f, -0.0714658f, 0.0f,
        0.437895f, 0.152598f, -0.885981f, 0.0f, -0.92394f, 0.353436f, -0.14635f, 0.0f,
        0.212189f, -0.815162f, -0.538969f, 0.0f, -0.859262f, 0.143405f, -0.491024f, 0.0f,
        0.991353f, 0.112814f, 0.0670273f, 0.0f, 0.0337884f, -0.979891f, -0.196654f, 0.0
    };
    inline constexpr array<int, 4> generator_noise = {
        1619,
        31337,
        6971,
        17642
    };
    inline constexpr int generator_seed = 1013;
    inline constexpr int generator_shift = 8;
    inline constexpr float sqrt_3 = 1.7320508075688772935f;

    template<unsigned int D>
    inline float gradient_coherent_noise(const array<float, D>& coords, int seed, noise_quality quality)
    {
        static_assert(D != 0, "noise dimension must be greater than 0");
        static_assert(D <= 4, "dimension higher than 4 has no noise implentation");
        //space cell coordinates respective to coords
        array<float, D> coords_low;
        std::transform(coords.begin(), coords.end(), coords_low.begin(), [](float v) {
            return v > 0.0f ? static_cast<int>(v) : static_cast<int>(v) - 1.0f;
        });
        array<float, D> coords_high;
        std::transform(coords_low.begin(), coords_low.end(), coords_high.begin(), [](float v) {
            return v + 1.0f;
        });
        
        array<float, D> coords_mid;

        switch (quality)
        {
        case gnoise::fast:
            for(size_t i=0;i<D;i++)
            {
                coords_mid[i] = coords[i] - coords_low[i];
            }
            break;
        case gnoise::standard:
            for (size_t i = 0; i < D; i++)
            {
                coords_mid[i] = map_cubic_scurve(coords[i] - coords_low[i]);
            }
            break;
        case gnoise::best:
            for (size_t i = 0; i < D; i++)
            {
                coords_mid[i] = map_quintic_scurve(coords[i] - coords_low[i]);
            }
            break;
        default:
            return 0.0f;
            break;
        }

        if constexpr(D == 1)
        {
            float x0 = gradient_noise<D>(coords, { static_cast<int>(coords_low[0]) }, seed);
            float x1 = gradient_noise<D>(coords, { static_cast<int>(coords_high[1]) }, seed);

            return interpolate_linear(x0, x1, coords_mid[0]);
        }
        if constexpr(D == 2)
        {
            array<int, D> coords_low_i;
            std::transform(coords_low.begin(), coords_low.end(), coords_low_i.begin(), [](float v) {
                return static_cast<int>(v);
            });
            array<int, D> coords_high_i;
            std::transform(coords_high.begin(), coords_high.end(), coords_high_i.begin(), [](float v) {
                return static_cast<int>(v);
            });

            float xy00 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1] }, seed);
            float xy10 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1] }, seed);
            float xy01 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1] }, seed);
            float xy11 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1] }, seed);

            //intermediate x result
            xy00 = interpolate_linear(xy00, xy10, coords_mid[0]);
            xy01 = interpolate_linear(xy01, xy11, coords_mid[0]);
            
            //generated result x * y
            return interpolate_linear(xy00, xy01, coords_mid[1]);
        }
        if constexpr(D == 3)
        {
            array<int, D> coords_low_i;
            std::transform(coords_low.begin(), coords_low.end(), coords_low_i.begin(), [](float v) {
                return static_cast<int>(v);
            });
            array<int, D> coords_high_i;
            std::transform(coords_high.begin(), coords_high.end(), coords_high_i.begin(), [](float v) {
                return static_cast<int>(v);
            });

            float xyz000 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_low_i[2] }, seed);
            float xyz010 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_low_i[2] }, seed);
            float xyz001 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_high_i[2] }, seed);
            float xyz011 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_high_i[2] }, seed);

            float xyz100 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_low_i[2] }, seed);
            float xyz110 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_low_i[2] }, seed);
            float xyz101 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_high_i[2] }, seed);
            float xyz111 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_high_i[2] }, seed);

            //intermediate x result
            xyz000 = interpolate_linear(xyz000, xyz100, coords_mid[0]);
            xyz010 = interpolate_linear(xyz010, xyz110, coords_mid[0]);
            xyz001 = interpolate_linear(xyz001, xyz101, coords_mid[0]);
            xyz011 = interpolate_linear(xyz011, xyz111, coords_mid[0]);
            
            //intermediate y result
            xyz000 = interpolate_linear(xyz000, xyz010, coords_mid[1]);
            xyz001 = interpolate_linear(xyz001, xyz011, coords_mid[1]);

            //generated result x * y * z
            return interpolate_linear(xyz000, xyz001, coords_mid[2]);
        }
        if constexpr(D == 4)
        {
            array<int, D> coords_low_i;
            std::transform(coords_low.begin(), coords_low.end(), coords_low_i.begin(), [](float v) {
                return static_cast<int>(v);
            });
            array<int, D> coords_high_i;
            std::transform(coords_high.begin(), coords_high.end(), coords_high_i.begin(), [](float v) {
                return static_cast<int>(v);
            });

            float xyzw0000 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_low_i[2], coords_low_i[3] }, seed);
            float xyzw0010 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_high_i[2], coords_low_i[3] }, seed);
            float xyzw0001 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_low_i[2], coords_high_i[3] }, seed);
            float xyzw0011 = gradient_noise<D>(coords, { coords_low_i[0], coords_low_i[1], coords_high_i[2], coords_high_i[3] }, seed);

            float xyzw0100 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_low_i[2], coords_low_i[3] }, seed);
            float xyzw0110 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_high_i[2], coords_low_i[3] }, seed);
            float xyzw0101 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_low_i[2], coords_high_i[3] }, seed);
            float xyzw0111 = gradient_noise<D>(coords, { coords_low_i[0], coords_high_i[1], coords_high_i[2], coords_high_i[3] }, seed);

            float xyzw1000 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_low_i[2], coords_low_i[3] }, seed);
            float xyzw1010 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_high_i[2], coords_low_i[3] }, seed);
            float xyzw1001 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_low_i[2], coords_high_i[3] }, seed);
            float xyzw1011 = gradient_noise<D>(coords, { coords_high_i[0], coords_low_i[1], coords_high_i[2], coords_high_i[3] }, seed);

            float xyzw1100 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_low_i[2], coords_low_i[3] }, seed);
            float xyzw1110 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_high_i[2], coords_low_i[3] }, seed);
            float xyzw1101 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_low_i[2], coords_high_i[3] }, seed);
            float xyzw1111 = gradient_noise<D>(coords, { coords_high_i[0], coords_high_i[1], coords_high_i[2], coords_high_i[3] }, seed);

            //intermediate x result
            xyzw0000 = interpolate_linear(xyzw0000, xyzw1000, coords_mid[0]);
            xyzw0100 = interpolate_linear(xyzw0100, xyzw1100, coords_mid[0]);
            xyzw0010 = interpolate_linear(xyzw0010, xyzw1010, coords_mid[0]);
            xyzw0110 = interpolate_linear(xyzw0110, xyzw1110, coords_mid[0]);

            xyzw0001 = interpolate_linear(xyzw0001, xyzw1001, coords_mid[0]);
            xyzw0101 = interpolate_linear(xyzw0101, xyzw1101, coords_mid[0]);
            xyzw0011 = interpolate_linear(xyzw0011, xyzw1011, coords_mid[0]);
            xyzw0111 = interpolate_linear(xyzw0111, xyzw1111, coords_mid[0]);

            //intermediate y result
            xyzw0000 = interpolate_linear(xyzw0000, xyzw0100, coords_mid[1]);
            xyzw0010 = interpolate_linear(xyzw0010, xyzw0110, coords_mid[1]);
            xyzw0001 = interpolate_linear(xyzw0001, xyzw0101, coords_mid[1]);
            xyzw0011 = interpolate_linear(xyzw0011, xyzw0111, coords_mid[1]);

            //intermediate z result
            xyzw0000 = interpolate_linear(xyzw0000, xyzw0010, coords_mid[2]);
            xyzw0001 = interpolate_linear(xyzw0001, xyzw0011, coords_mid[2]);

            //generated result x * y * z * w
            return interpolate_linear(xyzw0000, xyzw0001, coords_mid[3]);
        }

        return 0.0f;
    }
    
    template<unsigned int D>
    inline float gradient_noise(const array<float, D>& coords_f, const array<int, D>& coords_i, int seed)
    {
        static_assert(D != 0, "noise dimension must be greater than 0");
        static_assert(D <= 4, "dimension higher than 4 has no noise implentation");

        int i = std::inner_product(coords_i.begin(), coords_i.end(), generator_noise.begin(), 0);
        i += generator_seed * seed;
        i &= 0xffffffff;
        i ^= (i >> generator_shift);
        i &= 0xff;
        i <<= 2;
        array<float, D> coords_vg;
        std::copy(randoms.begin() + i, randoms.begin() + i + D, coords_vg.begin());
        array<float, D> coords_vp;
        for (size_t j = 0; j < D; j++)
        {
            coords_vp[j] = coords_f[j] - coords_i[j];
        }
        return std::inner_product(coords_vg.begin(), coords_vg.end(), coords_vp.begin(), 0.0f) * 2.12f;
    }

    inline float interpolate_cubic(float a, float b, float c, float d, float x)
    {
        float ab = a - b;
        float ca = c - a;
        float dc = d - c;
        float x2 = x * x;
        float x3 = x2 * x;
        return (dc - ab)*x3 + (2 * ab - dc)*x2 + ca * x + b;
    }

    inline float interpolate_linear(float a, float b, float x)
    {
        return (1.0f - x)*a + x * b;
    }

    inline float make_int32_range(float x)
    {
        if (x >= 1073741824.0f)
        {
            return (2.0f * fmod(x, 1073741824.0f)) - 1073741824.0f;
        }
        if (x <= -1073741824.0f)
        {
            return (2.0f * fmod(x, 1073741824.0f)) + 1073741824.0f;
        }
        return x;
    }

    inline float map_cubic_scurve(float x)
    {
        return x * x * (3.0f - 2.0f * x);
    }

    inline float map_quintic_scurve(float x)
    {
        float a3 = x * x * x;
        float a4 = a3 * x;
        float a5 = a4 * x;
        return (6.0f * a5) - (15.0f * a4) + (10.0f * a3);
    }

    template<unsigned int D>
    inline float value_noise(const array<int, D>& coords, int seed)
    {
        static_assert(D != 0, "noise dimension must be greater than 0");
        static_assert(D <= 4, "dimension higher than 4 has no noise implentation");

        return 1.0f - value_noise_int(coords, seed) / 1073741824.0f;
    }

    template<unsigned int D>
    inline long value_noise_int(const array<int, D>& coords, int seed)
    {
        static_assert(D != 0, "noise dimension must be greater than 0");
        static_assert(D <= 4, "dimension higher than 4 has no noise implentation");

        long n = std::inner_product(coords.begin(), coords.end(), generator_noise.begin(), generator_seed * seed);
        n &= 0x7fffffff;
        n = (n >> 13) ^ n;
        return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    }

    inline float clamp(float x, float min, float max)
    {
        return std::max(min, std::min(x, max));
    }

    template<unsigned int D, class MT, class P>
    inline vector<float> value_points_stcpu(const MT* module, const vector<vectorf<D>>& points, P predicate)
    {
        vector<float> values(points.size());
        std::transform(points.begin(), points.end(), values.begin(), [&module, &predicate](const vectorf<D>& v) {
            return predicate(module, v);
        });
        return values;
    }

    template<unsigned int D, class MT, class P>
    inline vector<float> value_points_mtcpu(const MT* module, const vector<vectorf<D>>& points, P predicate)
    {
        vector<float> values(points.size());
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
            auto thread_start_values_it = values.begin() + static_cast<size_t>(div * i);
            work_threads[i] = std::thread([thread_start_it, thread_end_it, thread_start_values_it, &values, &points, &module, &predicate]() {
                std::transform(thread_start_it, thread_end_it, thread_start_values_it, [&module, &predicate](const vectorf<D>& v) {
                    return predicate(module, v);
                });
            });
        }

        for (auto& thread : work_threads)
        {
            thread.join();
        }

        return values;
    }

    template<unsigned int D, class MT, class P>
    inline vector<float> value_range_stcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate)
    {
        unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());
        vector<float> values(precision_all_dim);
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

            for (size_t j = 0; j < D; j++)
            {
                coords.coords[j] = generator_utility::interpolate_linear(range[j].coords[0], range[j].coords[1], coords.coords[j]);
            }

            values[i] = predicate(module, coords);
        }

        return values;
    }

    template<unsigned int D, class MT, class P>
    inline vector<float> value_range_mtcpu(const MT* module, const rangef<D>& range, const precision<D>& precision, P predicate)
    {
        unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());
        vector<float> values(precision_all_dim);

        auto affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

        auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
        if (cores_assigned == 0)
        {
            return vector<float>();
        }

        vector<std::thread> work_threads(cores_assigned);
        auto div = static_cast<double>(precision_all_dim) / cores_assigned;
        for (size_t i = 0; i < work_threads.size(); i++)
        {
            auto thread_start_it = static_cast<size_t>(div * i);
            auto thread_end_it = static_cast<size_t>(div * (i + 1));

            work_threads[i] = std::thread([thread_start_it, thread_end_it, &values, &range, &precision, &module, &predicate]() {
                for (unsigned long long int i = thread_start_it; i < thread_end_it; i++)
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

                    for (size_t j = 0; j < D; j++)
                    {
                        coords.coords[j] = generator_utility::interpolate_linear(range[j].coords[0], range[j].coords[1], coords.coords[j]);
                    }

                    values[i] = predicate(module, coords);
                }
            });
        }

        for (auto& thread : work_threads)
        {
            thread.join();
        }

        return values;
    }
}

class noise_generator_module_base : public noise_module
{
protected:
    noise_generator_module_base() noexcept = default;
public:
    virtual gnoise::module_type                     module_type() const override;
};

template<class F, class D>
class noise_generator_module_def_impl : public noise_generator_module_base
{
protected:
    noise_generator_module_def_impl() noexcept :
        noise_generator_module_base()
    {
    }
    virtual ~noise_generator_module_def_impl() noexcept override
    {
        for (auto& k : _gpu_program_kernels_points)
        {
            if (k)
            {
                clReleaseKernel(k);
                k = nullptr;
            }
        }
        for (auto& p : _gpu_programs_points)
        {
            if (p)
            {
                clReleaseProgram(p);
                p = nullptr;
            }
        }

        for (auto& k : _gpu_program_kernels_ranges)
        {
            if (k)
            {
                clReleaseKernel(k);
                k = nullptr;
            }
        }
        for (auto& p : _gpu_programs_ranges)
        {
            if (p)
            {
                clReleaseProgram(p);
                p = nullptr;
            }
        }

        if (_gpu_command_queue)
        {
            clFlush(_gpu_command_queue);
            clFinish(_gpu_command_queue);
            clReleaseCommandQueue(_gpu_command_queue);
            _gpu_command_queue = nullptr;
        }
        if (_gpu_context)
        {
            clReleaseContext(_gpu_context);
            _gpu_context = nullptr;
        }
    }
public:
    virtual float                                   compute(const vector1f& point) const override
    {
        return F::generate(reinterpret_cast<const D*>(this), point);
    }
    virtual float                                   compute(const vector2f& point) const override
    {
        return F::generate(reinterpret_cast<const D*>(this), point);
    }
    virtual float                                   compute(const vector3f& point) const override
    {
        return F::generate(reinterpret_cast<const D*>(this), point);
    }
    virtual float                                   compute(const vector4f& point) const override
    {
        return F::generate(reinterpret_cast<const D*>(this), point);
    }

    virtual vector<float>                           compute(const vector<vector1f>& points) const override
    {
        if (points.size() == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_points_stcpu(reinterpret_cast<const D*>(this), points, F::generate<1>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::generate<1>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_points(points);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector2f>& points) const override
    {
        if (points.size() == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_points_stcpu(reinterpret_cast<const D*>(this), points, F::generate<2>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::generate<2>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_points(points);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector3f>& points) const override
    {
        if (points.size() == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_points_stcpu(reinterpret_cast<const D*>(this), points, F::generate<3>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::generate<3>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_points(points);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const vector<vector4f>& points) const override 
    {
        if (points.size() == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_points_stcpu(reinterpret_cast<const D*>(this), points, F::generate<4>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_points_mtcpu(reinterpret_cast<const D*>(this), points, F::generate<4>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_points(points);
        }
        break;
        }

        return vector<float>();
    }

    virtual vector<float>                           compute(const range1f& range, const precision1& precision) const override
    {
        if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<1>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<1>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_ranges(range, precision);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range2f& range, const precision2& precision) const override
    {
        if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<2>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<2>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_ranges(range, precision);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range3f& range, const precision3& precision) const override
    {
        if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<3>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<3>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_ranges(range, precision);
        }
        break;
        }

        return vector<float>();
    }
    virtual vector<float>                           compute(const range4f& range, const precision4& precision) const override
    {
        if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
        {
            return vector<float>();
        }

        switch (_configuration.computation_target())
        {
        case module_computation_target::single_thread_cpu:
        {
            return generator_utility::value_range_stcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<4>);
        }
        break;
        case module_computation_target::multi_thread_cpu:
        {
            return generator_utility::value_range_mtcpu(reinterpret_cast<const D*>(this), range, precision, F::generate<4>);
        }
        break;
        case module_computation_target::open_cl:
        {
            return compute_gpu_ranges(range, precision);
        }
        break;
        }

        return vector<float>();
    }
protected:
    virtual void                                    on_configuration_changed() override
    {
        for(auto& k : _gpu_program_kernels_points)
        {
            if (k)
            {
                clReleaseKernel(k);
                k = nullptr;
            }
        }
        for (auto& p : _gpu_programs_points)
        {
            if (p)
            {
                clReleaseProgram(p);
                p = nullptr;
            }
        }
        
        for (auto& k : _gpu_program_kernels_ranges)
        {
            if (k)
            {
                clReleaseKernel(k);
                k = nullptr;
            }
        }
        for (auto& p : _gpu_programs_ranges)
        {
            if (p)
            {
                clReleaseProgram(p);
                p = nullptr;
            }
        }

        if (_gpu_command_queue)
        {
            clFlush(_gpu_command_queue);
            clFinish(_gpu_command_queue);
            clReleaseCommandQueue(_gpu_command_queue);
            _gpu_command_queue = nullptr;
        }
        if(_gpu_context)
        {
            clReleaseContext(_gpu_context);
            _gpu_context = nullptr;
        }
        
        if(configuration().computation_target() == module_computation_target::gpu)
        {
            if(auto gpu_config = configuration().accelerated_target_configuration())
            {
                auto target_device = gpu_config->target();
                if(target_device != nullptr)
                {
                    _gpu_context = clCreateContext(nullptr, 1, &target_device, nullptr, nullptr, nullptr);
                    if(_gpu_context == nullptr)
                    {
                        return;
                    }
                    _gpu_command_queue = clCreateCommandQueueWithProperties(_gpu_context, target_device, nullptr, nullptr);
                    if (_gpu_command_queue == nullptr)
                    {
                        return;
                    }
                    F::create_kernels(
                        target_device, _gpu_context,
                        _gpu_programs_points,
                        _gpu_program_kernels_points,
                        _gpu_programs_ranges,
                        _gpu_program_kernels_ranges
                    );
                }
            }
        }
    }
private:
    template<unsigned int DIM>
    inline vector<float>                            compute_gpu_points(const vector<vectorf<DIM>>& points) const
    {
        if(!_gpu_context || !_gpu_command_queue || !_gpu_program_kernels_points[DIM-1])
        {
            return vector<float>();
        }

        auto module_config_i = F::get_module_config_i(reinterpret_cast<const D*>(this));
        auto module_config_f = F::get_module_config_f(reinterpret_cast<const D*>(this));

        //passing settings to gpu

        cl_mem buffer_randoms = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(float) * generator_utility::randoms.size(), nullptr, nullptr);
        cl_mem buffer_generator_defaults = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(int) * (generator_utility::generator_noise.size() + 2), nullptr, nullptr);
        cl_mem buffer_module_config_f = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(float) * module_config_f.size(), nullptr, nullptr);
        cl_mem buffer_module_config_i = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(int) * module_config_i.size(), nullptr, nullptr);

        array<int, generator_utility::generator_noise.size() + 2> generator_defaults;
        std::copy(generator_utility::generator_noise.begin(), generator_utility::generator_noise.end(), generator_defaults.begin());
        generator_defaults[generator_defaults.size() - 2] = generator_utility::generator_seed;
        generator_defaults[generator_defaults.size() - 1] = generator_utility::generator_shift;

        clEnqueueWriteBuffer(_gpu_command_queue, buffer_randoms, CL_FALSE, 0, 
            sizeof(float) * generator_utility::randoms.size(), generator_utility::randoms.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_generator_defaults, CL_FALSE, 0,
            sizeof(int) * (generator_utility::generator_noise.size() + 2), generator_defaults.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_module_config_f, CL_FALSE, 0,
            sizeof(float) * module_config_f.size(), module_config_f.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_module_config_i, CL_FALSE, 0,
            sizeof(int) * module_config_i.size(), module_config_i.data(), 0, nullptr, nullptr);

        //result and points buffers

        cl_mem buffer_results = clCreateBuffer(_gpu_context, CL_MEM_READ_WRITE, sizeof(float) * points.size(), nullptr, nullptr);
        cl_mem buffer_points = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(vectorf<DIM>) * points.size(), nullptr, nullptr);

        clEnqueueWriteBuffer(_gpu_command_queue, buffer_points, CL_FALSE, 0,
            sizeof(vectorf<DIM>) * points.size(), points.data(), 0, nullptr, nullptr);

        //wait for transfer to gpu to end

        clFinish(_gpu_command_queue);

        //set buffers to kernel arguments

        auto& kernel = _gpu_program_kernels_points[DIM - 1];
        clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer_results);
        clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer_points);
        clSetKernelArg(kernel, 2, sizeof(cl_mem), &buffer_randoms);
        clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer_generator_defaults);
        clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer_module_config_f);
        clSetKernelArg(kernel, 5, sizeof(cl_mem), &buffer_module_config_i);

        //start computation
        auto points_size = points.size();
        clEnqueueNDRangeKernel(_gpu_command_queue, kernel, 1, nullptr, &points_size, nullptr, 0, nullptr, nullptr);

        //retrieve results
        vector<float> results(points.size());

        clEnqueueReadBuffer(_gpu_command_queue, buffer_results, CL_TRUE, 0,
            sizeof(float) * results.size(), results.data(), 0, nullptr, nullptr);

        clReleaseMemObject(buffer_results);
        clReleaseMemObject(buffer_points);
        clReleaseMemObject(buffer_randoms);
        clReleaseMemObject(buffer_generator_defaults);
        clReleaseMemObject(buffer_module_config_f);
        clReleaseMemObject(buffer_module_config_i);

        clFinish(_gpu_command_queue);

        return results;
    }
    template<unsigned int DIM>
    inline vector<float>                            compute_gpu_ranges(const rangef<DIM>& range, const precision<DIM>& precision) const
    {
        if (!_gpu_context || !_gpu_command_queue || !_gpu_program_kernels_ranges[DIM - 1])
        {
            return vector<float>();
        }

        auto module_config_i = F::get_module_config_i(reinterpret_cast<const D*>(this));
        auto module_config_f = F::get_module_config_f(reinterpret_cast<const D*>(this));

        //passing settings to gpu

        cl_mem buffer_randoms = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(float) * generator_utility::randoms.size(), nullptr, nullptr);
        cl_mem buffer_generator_defaults = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(int) * (generator_utility::generator_noise.size() + 2), nullptr, nullptr);
        cl_mem buffer_module_config_f = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(float) * module_config_f.size(), nullptr, nullptr);
        cl_mem buffer_module_config_i = clCreateBuffer(_gpu_context, CL_MEM_READ_ONLY, sizeof(int) * module_config_i.size(), nullptr, nullptr);

        array<int, generator_utility::generator_noise.size() + 2> generator_defaults;
        std::copy(generator_utility::generator_noise.begin(), generator_utility::generator_noise.end(), generator_defaults.begin());
        generator_defaults[generator_defaults.size() - 2] = generator_utility::generator_seed;
        generator_defaults[generator_defaults.size() - 1] = generator_utility::generator_shift;

        clEnqueueWriteBuffer(_gpu_command_queue, buffer_randoms, CL_FALSE, 0,
            sizeof(float) * generator_utility::randoms.size(), generator_utility::randoms.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_generator_defaults, CL_FALSE, 0,
            sizeof(int) * (generator_utility::generator_noise.size() + 2), generator_defaults.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_module_config_f, CL_FALSE, 0,
            sizeof(float) * module_config_f.size(), module_config_f.data(), 0, nullptr, nullptr);
        clEnqueueWriteBuffer(_gpu_command_queue, buffer_module_config_i, CL_FALSE, 0,
            sizeof(int) * module_config_i.size(), module_config_i.data(), 0, nullptr, nullptr);

        //result and points buffers

        auto results_count = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());

        cl_mem buffer_results = clCreateBuffer(_gpu_context, CL_MEM_READ_WRITE, sizeof(float) * results_count, nullptr, nullptr);

        //wait for transfer to gpu to end

        clFinish(_gpu_command_queue);

        //set buffers to kernel arguments

        auto& kernel = _gpu_program_kernels_ranges[DIM - 1];
        clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer_results);
        clSetKernelArg(kernel, 1, sizeof(range), &range);
        clSetKernelArg(kernel, 2, sizeof(precision), &precision);
        clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer_randoms);
        clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer_generator_defaults);
        clSetKernelArg(kernel, 5, sizeof(cl_mem), &buffer_module_config_f);
        clSetKernelArg(kernel, 6, sizeof(cl_mem), &buffer_module_config_i);

        //start computation

        clEnqueueNDRangeKernel(_gpu_command_queue, kernel, 1, nullptr, &results_count, nullptr, 0, nullptr, nullptr);

        //retrieve results
        vector<float> results(results_count);

        clEnqueueReadBuffer(_gpu_command_queue, buffer_results, CL_TRUE, 0,
            sizeof(float) * results_count, results.data(), 0, nullptr, nullptr);

        clReleaseMemObject(buffer_results);
        clReleaseMemObject(buffer_randoms);
        clReleaseMemObject(buffer_generator_defaults);
        clReleaseMemObject(buffer_module_config_f);
        clReleaseMemObject(buffer_module_config_i);

        clFinish(_gpu_command_queue);

        return results;
    }
private:
    cl_context                                      _gpu_context = nullptr;

    mutable array<cl_program, 4>                    _gpu_programs_points = { nullptr, nullptr, nullptr, nullptr };
    mutable array<cl_kernel, 4>                     _gpu_program_kernels_points = { nullptr, nullptr, nullptr, nullptr };

    mutable array<cl_program, 4>                    _gpu_programs_ranges = { nullptr, nullptr, nullptr, nullptr };
    mutable array<cl_kernel, 4>                     _gpu_program_kernels_ranges = { nullptr, nullptr, nullptr, nullptr };

    mutable cl_command_queue                        _gpu_command_queue = nullptr;
};

GNOISE_NAMESPACE_END