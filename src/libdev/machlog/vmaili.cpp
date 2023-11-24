/*
 * V M A I L I . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "machlog/internal/vmaili.hpp"

MachLogVoiceMailImpl::MachLogVoiceMailImpl()
    : sampleHandleValid_(false)
{

    TEST_INVARIANT;
}

MachLogVoiceMailImpl::~MachLogVoiceMailImpl()
{
    TEST_INVARIANT;
}

void MachLogVoiceMailImpl::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachLogVoiceMailImpl& t)
{

    o << "MachLogVoiceMailImpl " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachLogVoiceMailImpl " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

/* End VMAILI.CPP ***************************************************/
