template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::xxx()
{
    return swizzle3(x(), x(), x());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::xxx() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::xxy()
{
    return swizzle3(x(), x(), y());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::xxy() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::xyx()
{
    return swizzle3(x(), y(), x());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::xyx() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::yxx()
{
    return swizzle3(y(), x(), x());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::yxx() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::xyy()
{
    return swizzle3(x(), y(), y());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::xyy() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::yxy()
{
    return swizzle3(y(), x(), y());
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::yxy() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::yyx()
{
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::yyx() const
{
}

template <typename _type>
_internal::swizzle_vectornt<3, value_type, vector3t<value_type>> YAMGP_SWIZZLE_VEC<_type>::yyy()
{
}

template <typename _type>
vector3t<value_type> YAMGP_SWIZZLE_VEC<_type>::yyy() const
{
}