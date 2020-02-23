#pragma once

namespace Ubpa {
	namespace detail {
        namespace IMatrix {
            template<size_t N>
            struct inverse;

            template<>
            struct inverse<3> {
                template<typename M>
                static const M run(const M& m) noexcept {
                    static_assert(M::N == 3, "M::N == 3");
                    using F = typename M::F;

                    F determinant = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                        + m[1][0] * (m[2][1] * m[0][2] - m[0][1] * m[2][2])
                        + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

                    assert(determinant != static_cast<F>(0));

                    F inverseDeterminant = static_cast<F>(1) / determinant;

                    M rst{};

                    rst[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * inverseDeterminant;
                    rst[1][0] = (m[2][0] * m[1][2] - m[1][0] * m[2][2]) * inverseDeterminant;
                    rst[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * inverseDeterminant;
                    rst[0][1] = (m[2][1] * m[0][2] - m[0][1] * m[2][2]) * inverseDeterminant;
                    rst[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * inverseDeterminant;
                    rst[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * inverseDeterminant;
                    rst[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * inverseDeterminant;
                    rst[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * inverseDeterminant;
                    rst[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * inverseDeterminant;

                    return rst;
                }
            };

            template<>
            struct inverse<4> {
                // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
                template<typename M>
                static const M run(const M& m) noexcept {
                    static_assert(M::N == 4, "M::N == 4");
                    using F = typename M::F;

                    M rst{};

                    rst[0][0] = m[1][1] * m[2][2] * m[3][3] -
                        m[1][1] * m[2][3] * m[3][2] -
                        m[2][1] * m[1][2] * m[3][3] +
                        m[2][1] * m[1][3] * m[3][2] +
                        m[3][1] * m[1][2] * m[2][3] -
                        m[3][1] * m[1][3] * m[2][2];

                    rst[1][0] = -m[1][0] * m[2][2] * m[3][3] +
                        m[1][0] * m[2][3] * m[3][2] +
                        m[2][0] * m[1][2] * m[3][3] -
                        m[2][0] * m[1][3] * m[3][2] -
                        m[3][0] * m[1][2] * m[2][3] +
                        m[3][0] * m[1][3] * m[2][2];

                    rst[2][0] = m[1][0] * m[2][1] * m[3][3] -
                        m[1][0] * m[2][3] * m[3][1] -
                        m[2][0] * m[1][1] * m[3][3] +
                        m[2][0] * m[1][3] * m[3][1] +
                        m[3][0] * m[1][1] * m[2][3] -
                        m[3][0] * m[1][3] * m[2][1];

                    rst[3][0] = -m[1][0] * m[2][1] * m[3][2] +
                        m[1][0] * m[2][2] * m[3][1] +
                        m[2][0] * m[1][1] * m[3][2] -
                        m[2][0] * m[1][2] * m[3][1] -
                        m[3][0] * m[1][1] * m[2][2] +
                        m[3][0] * m[1][2] * m[2][1];

                    rst[0][1] = -m[0][1] * m[2][2] * m[3][3] +
                        m[0][1] * m[2][3] * m[3][2] +
                        m[2][1] * m[0][2] * m[3][3] -
                        m[2][1] * m[0][3] * m[3][2] -
                        m[3][1] * m[0][2] * m[2][3] +
                        m[3][1] * m[0][3] * m[2][2];

                    rst[1][1] = m[0][0] * m[2][2] * m[3][3] -
                        m[0][0] * m[2][3] * m[3][2] -
                        m[2][0] * m[0][2] * m[3][3] +
                        m[2][0] * m[0][3] * m[3][2] +
                        m[3][0] * m[0][2] * m[2][3] -
                        m[3][0] * m[0][3] * m[2][2];

                    rst[2][1] = -m[0][0] * m[2][1] * m[3][3] +
                        m[0][0] * m[2][3] * m[3][1] +
                        m[2][0] * m[0][1] * m[3][3] -
                        m[2][0] * m[0][3] * m[3][1] -
                        m[3][0] * m[0][1] * m[2][3] +
                        m[3][0] * m[0][3] * m[2][1];

                    rst[3][1] = m[0][0] * m[2][1] * m[3][2] -
                        m[0][0] * m[2][2] * m[3][1] -
                        m[2][0] * m[0][1] * m[3][2] +
                        m[2][0] * m[0][2] * m[3][1] +
                        m[3][0] * m[0][1] * m[2][2] -
                        m[3][0] * m[0][2] * m[2][1];

                    rst[0][2] = m[0][1] * m[1][2] * m[3][3] -
                        m[0][1] * m[1][3] * m[3][2] -
                        m[1][1] * m[0][2] * m[3][3] +
                        m[1][1] * m[0][3] * m[3][2] +
                        m[3][1] * m[0][2] * m[1][3] -
                        m[3][1] * m[0][3] * m[1][2];

                    rst[1][2] = -m[0][0] * m[1][2] * m[3][3] +
                        m[0][0] * m[1][3] * m[3][2] +
                        m[1][0] * m[0][2] * m[3][3] -
                        m[1][0] * m[0][3] * m[3][2] -
                        m[3][0] * m[0][2] * m[1][3] +
                        m[3][0] * m[0][3] * m[1][2];

                    rst[2][2] = m[0][0] * m[1][1] * m[3][3] -
                        m[0][0] * m[1][3] * m[3][1] -
                        m[1][0] * m[0][1] * m[3][3] +
                        m[1][0] * m[0][3] * m[3][1] +
                        m[3][0] * m[0][1] * m[1][3] -
                        m[3][0] * m[0][3] * m[1][1];

                    rst[3][2] = -m[0][0] * m[1][1] * m[3][2] +
                        m[0][0] * m[1][2] * m[3][1] +
                        m[1][0] * m[0][1] * m[3][2] -
                        m[1][0] * m[0][2] * m[3][1] -
                        m[3][0] * m[0][1] * m[1][2] +
                        m[3][0] * m[0][2] * m[1][1];

                    rst[0][3] = -m[0][1] * m[1][2] * m[2][3] +
                        m[0][1] * m[1][3] * m[2][2] +
                        m[1][1] * m[0][2] * m[2][3] -
                        m[1][1] * m[0][3] * m[2][2] -
                        m[2][1] * m[0][2] * m[1][3] +
                        m[2][1] * m[0][3] * m[1][2];

                    rst[1][3] = m[0][0] * m[1][2] * m[2][3] -
                        m[0][0] * m[1][3] * m[2][2] -
                        m[1][0] * m[0][2] * m[2][3] +
                        m[1][0] * m[0][3] * m[2][2] +
                        m[2][0] * m[0][2] * m[1][3] -
                        m[2][0] * m[0][3] * m[1][2];

                    rst[2][3] = -m[0][0] * m[1][1] * m[2][3] +
                        m[0][0] * m[1][3] * m[2][1] +
                        m[1][0] * m[0][1] * m[2][3] -
                        m[1][0] * m[0][3] * m[2][1] -
                        m[2][0] * m[0][1] * m[1][3] +
                        m[2][0] * m[0][3] * m[1][1];

                    rst[3][3] = m[0][0] * m[1][1] * m[2][2] -
                        m[0][0] * m[1][2] * m[2][1] -
                        m[1][0] * m[0][1] * m[2][2] +
                        m[1][0] * m[0][2] * m[2][1] +
                        m[2][0] * m[0][1] * m[1][2] -
                        m[2][0] * m[0][2] * m[1][1];

                    F det = m[0][0] * rst[0][0] + m[0][1] * rst[1][0] + m[0][2] * rst[2][0] + m[0][3] * rst[3][0];

                    assert(det != static_cast<F>(0));

                    F invDet = static_cast<F>(1) / det;

                    rst *= invDet;

                    return rst;
                }

            };

            template<typename M>
            const M run_inverse(const M& m) noexcept {
                return inverse<M::N>::run(m);
            }

            // ----------------------

            template<size_t N>
            struct mul;

            template<>
            struct mul<3> {
                template<typename M>
                static const M run(const M& x, const M& y) noexcept {
                    static_assert(M::N == 3, "M::N == 3");
                    using F = typename M::F;

                    // must unloop by hand, complier may not auto unloop
                    F f00 = x(0, 0) * y(0, 0) + x(0, 1) * y(1, 0) + x(0, 2) * y(2, 0);
                    F f01 = x(0, 0) * y(0, 1) + x(0, 1) * y(1, 1) + x(0, 2) * y(2, 1);
                    F f02 = x(0, 0) * y(0, 2) + x(0, 1) * y(1, 2) + x(0, 2) * y(2, 2);
                    F f10 = x(1, 0) * y(0, 0) + x(1, 1) * y(1, 0) + x(1, 2) * y(2, 0);
                    F f11 = x(1, 0) * y(0, 1) + x(1, 1) * y(1, 1) + x(1, 2) * y(2, 1);
                    F f12 = x(1, 0) * y(0, 2) + x(1, 1) * y(1, 2) + x(1, 2) * y(2, 2);
                    F f20 = x(2, 0) * y(0, 0) + x(2, 1) * y(1, 0) + x(2, 2) * y(2, 0);
                    F f21 = x(2, 0) * y(0, 1) + x(2, 1) * y(1, 1) + x(2, 2) * y(2, 1);
                    F f22 = x(2, 0) * y(0, 2) + x(2, 1) * y(1, 2) + x(2, 2) * y(2, 2);

                    return std::array<F, 3 * 3>{
                        f00, f01, f02,
                        f10, f11, f12,
                        f20, f21, f22
                    };
                }
            };

            template<>
            struct mul<4> {
                template<typename M>
                static const M run(const M& x, const M& y) noexcept {
                    static_assert(M::N == 4, "M::N == 4");
                    using F = typename M::F;

                    // must unloop by hand, complier may not auto unloop
                    F f00 = x(0, 0) * y(0, 0) + x(0, 1) * y(1, 0) + x(0, 2) * y(2, 0) + x(0, 3) * y(3, 0);
                    F f01 = x(0, 0) * y(0, 1) + x(0, 1) * y(1, 1) + x(0, 2) * y(2, 1) + x(0, 3) * y(3, 1);
                    F f02 = x(0, 0) * y(0, 2) + x(0, 1) * y(1, 2) + x(0, 2) * y(2, 2) + x(0, 3) * y(3, 2);
                    F f03 = x(0, 0) * y(0, 3) + x(0, 1) * y(1, 3) + x(0, 2) * y(2, 3) + x(0, 3) * y(3, 3);
                    F f10 = x(1, 0) * y(0, 0) + x(1, 1) * y(1, 0) + x(1, 2) * y(2, 0) + x(1, 3) * y(3, 0);
                    F f11 = x(1, 0) * y(0, 1) + x(1, 1) * y(1, 1) + x(1, 2) * y(2, 1) + x(1, 3) * y(3, 1);
                    F f12 = x(1, 0) * y(0, 2) + x(1, 1) * y(1, 2) + x(1, 2) * y(2, 2) + x(1, 3) * y(3, 2);
                    F f13 = x(1, 0) * y(0, 3) + x(1, 1) * y(1, 3) + x(1, 2) * y(2, 3) + x(1, 3) * y(3, 3);
                    F f20 = x(2, 0) * y(0, 0) + x(2, 1) * y(1, 0) + x(2, 2) * y(2, 0) + x(2, 3) * y(3, 0);
                    F f21 = x(2, 0) * y(0, 1) + x(2, 1) * y(1, 1) + x(2, 2) * y(2, 1) + x(2, 3) * y(3, 1);
                    F f22 = x(2, 0) * y(0, 2) + x(2, 1) * y(1, 2) + x(2, 2) * y(2, 2) + x(2, 3) * y(3, 2);
                    F f23 = x(2, 0) * y(0, 3) + x(2, 1) * y(1, 3) + x(2, 2) * y(2, 3) + x(2, 3) * y(3, 3);
                    F f30 = x(3, 0) * y(0, 0) + x(3, 1) * y(1, 0) + x(3, 2) * y(2, 0) + x(3, 3) * y(3, 0);
                    F f31 = x(3, 0) * y(0, 1) + x(3, 1) * y(1, 1) + x(3, 2) * y(2, 1) + x(3, 3) * y(3, 1);
                    F f32 = x(3, 0) * y(0, 2) + x(3, 1) * y(1, 2) + x(3, 2) * y(2, 2) + x(3, 3) * y(3, 2);
                    F f33 = x(3, 0) * y(0, 3) + x(3, 1) * y(1, 3) + x(3, 2) * y(2, 3) + x(3, 3) * y(3, 3);

                    return std::array<F, 4 * 4>{
                        f00, f01, f02, f03,
                        f10, f11, f12, f13,
                        f20, f21, f22, f23,
                        f30, f31, f32, f33
                    };
                }
            };
            
            template<typename M>
            const M run_mul(const M& x, const M& y) noexcept {
                return mul<M::N>::run(x, y);
            }
        }

	}
}