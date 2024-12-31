#include "custorage.h"
#include <filesystem>
#include <fstream>

namespace curiox {

    std::unordered_map<Oid, std::unordered_map<RelFileNumber, std::filesystem::path>> Storage::fileCache; 
    std::filesystem::path Storage::defaultPath = "/tmp/curiox";

    void Storage::init(const std::string &path) {
        defaultPath = path;
        if (std::filesystem::exists(defaultPath)) {
            elog(INFO, "Storage directory already exist at path: %s", path.c_str());
            return;
        }
        if (std::filesystem::create_directories(defaultPath)) {
            elog(INFO, "Created storage directory: %s", path.c_str());
        } else {
            elog(WARNING, "Unable to create storage directory at path: %s", path.c_str());
        }
    }

    bool Storage::createOnDiskRelation(const Oid& dbOid, const RelFileNumber& relNumber) {

        if (fileCache[dbOid].find(relNumber) == fileCache[dbOid].end()) {
            fileCache[dbOid][relNumber] = defaultPath / (std::to_string(dbOid) + "-" +  std::to_string(relNumber));
            std::ofstream file(fileCache[dbOid][relNumber].c_str());
            if (file.is_open()) {
                elog(INFO, "Created on-disk relation with database oid: %d, relation number: %d", dbOid, relNumber);
                return true;
            } else {
                elog(WARNING, "Unable to create on-disk relation with database oid: %d, relation number: %d", dbOid, relNumber);
                return false;
            }
        } else {
            elog(WARNING, "Relation with database oid: %d, relation number: %d already exists", dbOid, relNumber);
            return true;
        }
    }

    bool Storage::deleteOnDiskRelation(const Oid& dbOid, const RelFileNumber& relNumber) {
        if (fileCache.find(dbOid) != fileCache.end() && fileCache[dbOid].find(relNumber) != fileCache[dbOid].end()) {
            std::string filePath = fileCache[dbOid][relNumber];
            if (std::filesystem::remove(filePath)) {
                elog(INFO, "Deleted on-disk relation with database oid: %d, relation number: %d", dbOid, relNumber);
                fileCache[dbOid].erase(relNumber);
                if (fileCache[dbOid].empty()) {
                    fileCache.erase(dbOid);
                }
                return true;
            } else {
                elog(WARNING, "Unable to delete on-disk relation with database oid: %d, relation number: %d", dbOid, relNumber);
                return false;
            }
        } else {
            elog(WARNING, "Relation with database oid: %d, relation number: %d does not exist", dbOid, relNumber);
            return false;
        }
    }
}