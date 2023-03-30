/*
 * S E R I A M A P . H P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

/*
    FtlSerialMap

    Implements a map from FtlSerialId to objects of class VALUE, over
    which the class is parameterized.
*/

#ifndef FTL_SERIAMAP_HPP
#define FTL_SERIAMAP_HPP

#include "ftl/serialid.hpp"

#include <unordered_map>

// Orthodox canonical
template <class VALUE> class FtlSerialMap : public std::unordered_map<FtlSerialId, VALUE>
{
public:
    FtlSerialMap() = default;

    using Key = FtlSerialId;
    using Value = VALUE;
    using KeyValueAssoc = std::pair<FtlSerialId, Value>;

    using std::unordered_map<FtlSerialId, Value>::operator[];

    const Value& operator[](const Key& key) const;

    bool contains(const FtlSerialId& id) const;

    void add(const std::pair<FtlSerialId, Value>& addMe);

    void remove(const FtlSerialId& id);
};

template <class VALUE> inline const VALUE& FtlSerialMap<VALUE>::operator[](const Key& key) const
{
    auto it = std::unordered_map<FtlSerialId, VALUE>::find(key);
    if (it != std::unordered_map<FtlSerialId, VALUE>::end())
    {
        return it->second;
    }

    return VALUE();
}

template <class VALUE> inline bool FtlSerialMap<VALUE>::contains(const FtlSerialId& id) const
{
    return std::unordered_map<FtlSerialId, VALUE>::find(id) != std::unordered_map<FtlSerialId, VALUE>::end();
}

template <class VALUE> inline void FtlSerialMap<VALUE>::add(const std::pair<FtlSerialId, VALUE>& addMe)
{
    std::unordered_map<FtlSerialId, VALUE>::emplace(addMe.first, addMe.second);
}

template <class VALUE> inline void FtlSerialMap<VALUE>::remove(const FtlSerialId& id)
{
    std::unordered_map<FtlSerialId, VALUE>::erase(id);
}

#endif // FTL_SERIAMAP_HPP

/* End SERIAMAP.HPP *************************************************/
