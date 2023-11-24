/*
 * P U L S A U R A . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "mathex/point2d.hpp"
#include "machphys/pulsaura.hpp"
#include "machphys/private/otherper.hpp"
#include "ctl/vector.hpp"
#include "world4d/entyplan.hpp"
#include "world4d/visplan.hpp"
#include "world4d/gusplan.hpp"

#include "render/mesh.hpp"
#include "render/meshinst.hpp"
#include "render/material.hpp"
#include "render/matvec.hpp"
#include "render/colour.hpp"

#include "phys/lsclplan.hpp"

#include "system/pathname.hpp"

PER_DEFINE_PERSISTENT(MachPhysPulseAura);

// One-time ctor
MachPhysPulseAura::MachPhysPulseAura()
    : W4dEntity(MachPhysOtherPersistence::instance().pRoot(), MexTransform3d(), W4dEntity::NOT_SOLID)
{
    // Load the mesh data
    readLODFile(SysPathName("models/weapons/splat/pulse/aura.lod"));
    TEST_INVARIANT;
}

// public ctor
MachPhysPulseAura::MachPhysPulseAura(W4dEntity* pParent, const MexTransform3d& localTransform)
    : W4dEntity(exemplar(), pParent, localTransform)
{
    // make invisible until required
    visible(false);
    TEST_INVARIANT;
}

MachPhysPulseAura::MachPhysPulseAura(PerConstructor con)
    : W4dEntity(con)
{
}

MachPhysPulseAura::~MachPhysPulseAura()
{
    TEST_INVARIANT;
}

// static
const MachPhysPulseAura& MachPhysPulseAura::exemplar()
{
    return MachPhysOtherPersistence::instance().pulseAuraExemplar();
}

void MachPhysPulseAura::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachPhysPulseAura& t)
{

    o << "MachPhysPulseAura " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachPhysPulseAura " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

// virtual
bool MachPhysPulseAura::intersectsLine(const MexLine3d&, MATHEX_SCALAR*, Accuracy) const
{
    return false;
}

void perWrite(PerOstream& ostr, const MachPhysPulseAura& scorch)
{
    const W4dEntity& base = scorch;

    ostr << base;
}

void perRead(PerIstream& istr, MachPhysPulseAura& scorch)
{
    W4dEntity& base = scorch;

    istr >> base;
}

void MachPhysPulseAura::startPulseAura(const PhysAbsoluteTime& startTime, const PhysRelativeTime& duration)
{
    /*
    //set the colour
    Ren::ConstMeshPtr animMeshPtr = _CONST_CAST(const W4dEntity*, this)->mesh().mesh();
    RenMaterialVec* pAnimMaterialVec =animMeshPtr->materialVec().release();

    (*pAnimMaterialVec)[0].diffuse( RenColour( 0, 188.0/255.0, 0) );
*/
    // Counted pointers etc for standard plans
    static W4dVisibilityPlanPtr visibilityPlanPtr;
    static W4dScalePlanPtr scalePlanPtr;

    // First time set up standard plans
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;

        // Create the visibility plan
        W4dVisibilityPlan* pVisibilityPlan = new W4dVisibilityPlan(true);
        pVisibilityPlan->add(false, duration);
        visibilityPlanPtr = pVisibilityPlan;

        // scale plan
        PhysRelativeTime interval = duration / 3.0;
        PhysLinearScalarPlan::ScalarVec times;
        times.reserve(3);
        times.push_back(interval);
        times.push_back(interval * 2.0);
        times.push_back(duration);

        PhysLinearScalarPlan::ScalarVec scales;
        scales.reserve(4);
        scales.push_back(1);
        scales.push_back(2);
        scales.push_back(1);
        scales.push_back(0.5);

        scalePlanPtr = new W4dGeneralUniformScalePlan(new PhysLinearScalarPlan(times, scales));
    }

    // Set its visibility plan
    W4dEntityPlan& entityPlan = entityPlanForEdit();
    entityPlan.visibilityPlan(visibilityPlanPtr, startTime);

    // Set the scaling plan
    entityPlan.scalePlan(scalePlanPtr, startTime);
}
/* End PULSAURA.CPP *************************************************/
