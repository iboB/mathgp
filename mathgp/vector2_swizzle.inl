value_type& y()
{
    return at(1);
}

const value_type& y() const
{
    return at(1);
}

vector2t<_type>& xy()
{
    return reinterpret_cast<vector2t<_type>*>(as_array());
}

const vector2t<_type>& xy() const
{
    return reinterpret_cast<vector2t<_type>*>(as_array());
}