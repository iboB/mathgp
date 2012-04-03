
template <typename _type>
_internal::swizzle_vectornt<2, _type, vector2t<_type>> YAMGP_SWIZZLE_VEC<_type>::xx()
{
    return swizzle2(x(), x());
}

template <typename _type>
vector2t<_type> YAMGP_SWIZZLE_VEC<_type>::xx() const
{
    return vector2t<_type>::coord(x(), x());
}

template <typename _type>
_internal::swizzle_vectornt<3, _type, vector3t<_type>> YAMGP_SWIZZLE_VEC<_type>::xxx()
{
    return swizzle3(x(), x(), x());
}

template <typename _type>
vector3t<_type> YAMGP_SWIZZLE_VEC<_type>::xxx() const
{
    return vector3t<_type>::coord(x(), x(), x());
}