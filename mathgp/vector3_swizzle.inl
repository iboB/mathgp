value_type& x()
{
    return at(0);
}

const value_type& x() const
{
    return at(0);
}

_internal::swizzle_vectornt<2, _type, vector2t<_type>> xx();

vector2t<_type> xx() const;

_internal::swizzle_vectornt<3, _type, vector3t<_type>> xxx();

vector3t<_type> xxx() const;
