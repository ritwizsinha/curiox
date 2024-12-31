#include <string>
#include <unordered_map>
#include <filesystem>

#ifdef __cplusplus
extern "C" {
#endif

#include "postgres.h"
#include "common/relpath.h"

#ifdef __cplusplus
}
#endif

namespace curiox {
    class Storage {
    public:
        static void init(const std::string &path = "/tmp/curiox");
        static bool createOnDiskRelation(const Oid&, const RelFileNumber&);
        static bool deleteOnDiskRelation(const Oid&, const RelFileNumber&);

    private:
        static std::unordered_map<Oid, std::unordered_map<RelFileNumber, std::filesystem::path>> fileCache;
        static std::filesystem::path defaultPath;
    };
}