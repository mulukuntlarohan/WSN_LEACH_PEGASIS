//
// Generated file, do not edit! Created by opp_msgtool 6.3 from NetworkPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "NetworkPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(WsnPacketType, (WsnPacketType::DATA, WsnPacketType::HELLO, WsnPacketType::CH_ADV, WsnPacketType::JOIN_REQ, WsnPacketType::TDMA_SCH));

Register_Class(NetworkPacket)

NetworkPacket::NetworkPacket() : ::inet::FieldsChunk()
{
}

NetworkPacket::NetworkPacket(const NetworkPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

NetworkPacket::~NetworkPacket()
{
}

NetworkPacket& NetworkPacket::operator=(const NetworkPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void NetworkPacket::copy(const NetworkPacket& other)
{
    this->srcId = other.srcId;
    this->destId = other.destId;
    this->type = other.type;
    this->sequenceNumber = other.sequenceNumber;
    this->residualEnergy = other.residualEnergy;
    this->xPos = other.xPos;
    this->yPos = other.yPos;
}

void NetworkPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->residualEnergy);
    doParsimPacking(b,this->xPos);
    doParsimPacking(b,this->yPos);
}

void NetworkPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->residualEnergy);
    doParsimUnpacking(b,this->xPos);
    doParsimUnpacking(b,this->yPos);
}

int NetworkPacket::getSrcId() const
{
    return this->srcId;
}

void NetworkPacket::setSrcId(int srcId)
{
    handleChange();
    this->srcId = srcId;
}

int NetworkPacket::getDestId() const
{
    return this->destId;
}

void NetworkPacket::setDestId(int destId)
{
    handleChange();
    this->destId = destId;
}

int NetworkPacket::getType() const
{
    return this->type;
}

void NetworkPacket::setType(int type)
{
    handleChange();
    this->type = type;
}

int NetworkPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void NetworkPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

double NetworkPacket::getResidualEnergy() const
{
    return this->residualEnergy;
}

void NetworkPacket::setResidualEnergy(double residualEnergy)
{
    handleChange();
    this->residualEnergy = residualEnergy;
}

double NetworkPacket::getXPos() const
{
    return this->xPos;
}

void NetworkPacket::setXPos(double xPos)
{
    handleChange();
    this->xPos = xPos;
}

double NetworkPacket::getYPos() const
{
    return this->yPos;
}

void NetworkPacket::setYPos(double yPos)
{
    handleChange();
    this->yPos = yPos;
}

class NetworkPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcId,
        FIELD_destId,
        FIELD_type,
        FIELD_sequenceNumber,
        FIELD_residualEnergy,
        FIELD_xPos,
        FIELD_yPos,
    };
  public:
    NetworkPacketDescriptor();
    virtual ~NetworkPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(NetworkPacketDescriptor)

NetworkPacketDescriptor::NetworkPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(NetworkPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

NetworkPacketDescriptor::~NetworkPacketDescriptor()
{
    delete[] propertyNames;
}

bool NetworkPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NetworkPacket *>(obj)!=nullptr;
}

const char **NetworkPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NetworkPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NetworkPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int NetworkPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_residualEnergy
        FD_ISEDITABLE,    // FIELD_xPos
        FD_ISEDITABLE,    // FIELD_yPos
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *NetworkPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcId",
        "destId",
        "type",
        "sequenceNumber",
        "residualEnergy",
        "xPos",
        "yPos",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int NetworkPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "residualEnergy") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "xPos") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "yPos") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *NetworkPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_srcId
        "int",    // FIELD_destId
        "int",    // FIELD_type
        "int",    // FIELD_sequenceNumber
        "double",    // FIELD_residualEnergy
        "double",    // FIELD_xPos
        "double",    // FIELD_yPos
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **NetworkPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NetworkPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "WsnPacketType";
            if (!strcmp(propertyName, "enum")) return "WsnPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int NetworkPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NetworkPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NetworkPacket'", field);
    }
}

const char *NetworkPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NetworkPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: return long2string(pp->getSrcId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_type: return enum2string(static_cast<int>(pp->getType()), "WsnPacketType");
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_residualEnergy: return double2string(pp->getResidualEnergy());
        case FIELD_xPos: return double2string(pp->getXPos());
        case FIELD_yPos: return double2string(pp->getYPos());
        default: return "";
    }
}

void NetworkPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: pp->setSrcId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_type: pp->setType((WsnPacketType)string2enum(value, "WsnPacketType")); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_residualEnergy: pp->setResidualEnergy(string2double(value)); break;
        case FIELD_xPos: pp->setXPos(string2double(value)); break;
        case FIELD_yPos: pp->setYPos(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkPacket'", field);
    }
}

omnetpp::cValue NetworkPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: return pp->getSrcId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_type: return pp->getType();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_residualEnergy: return pp->getResidualEnergy();
        case FIELD_xPos: return pp->getXPos();
        case FIELD_yPos: return pp->getYPos();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NetworkPacket' as cValue -- field index out of range?", field);
    }
}

void NetworkPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcId: pp->setSrcId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_type: pp->setType((WsnPacketType)value.intValue()); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_residualEnergy: pp->setResidualEnergy(value.doubleValue()); break;
        case FIELD_xPos: pp->setXPos(value.doubleValue()); break;
        case FIELD_yPos: pp->setYPos(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkPacket'", field);
    }
}

const char *NetworkPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr NetworkPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NetworkPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkPacket *pp = omnetpp::fromAnyPtr<NetworkPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkPacket'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

