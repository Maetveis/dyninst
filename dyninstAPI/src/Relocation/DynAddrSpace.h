/* Plugin Implementation */

#ifndef PATCHAPI_H_DYNINST_DYNADDRSPACE_H_
#define PATCHAPI_H_DYNINST_DYNADDRSPACE_H_

#include "DynCommon.h"

namespace Dyninst {
namespace PatchAPI {

class DynAddrSpace : public AddrSpace {
  public:
    static DynAddrSpacePtr create(PatchObject* obj, AddressSpace* as);
    bool loadLibrary(PatchObject*, AddressSpace* as);
    bool initAs(PatchObject* obj, AddressSpace* as);

    typedef std::map<ParseAPI::CodeObject*, AddressSpace*> CoAsMap;
    CoAsMap& coas_map() { return coas_map_; }

    virtual bool write(PatchObject*, Address to, Address from, size_t size);
    virtual Address malloc(PatchObject*, size_t size, Address near);
    virtual bool realloc(PatchObject*, Address orig, size_t size);
    virtual bool free(PatchObject*, Address orig);

    bool isRecursive() { return recursive_; }
    void setRecursive(bool r) { recursive_ = r; }

  protected:
    DynAddrSpace();
    DynAddrSpace(AddrSpacePtr par);

    CoAsMap coas_map_;
    AddressSpace* first_as_;
    bool recursive_;
};

}
}
#endif  // PATCHAPI_H_DYNINST_DYNADDRSPACE_H_
