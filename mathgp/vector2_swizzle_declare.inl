value_type& y()
{
    return at(1);
}

const value_type& y() const
{
    return at(1);
}

vector2t<value_type>& xy()
{
    return *reinterpret_cast<vector2t<value_type>*>(this);
}

const vector2t<value_type>& xy() const
{
    return *reinterpret_cast<const vector2t<value_type>*>(this);
}

_internal::swizzle_vectornt<2, value_type, vector2t<value_type>> yx();


vector2t<value_type> yx() const;

_internal::swizzle_vectornt<2, value_type, vector2t<value_type>> yy();
vector2t<value_type> yy() const
{
    return vector2t::coord(y(), y());
}