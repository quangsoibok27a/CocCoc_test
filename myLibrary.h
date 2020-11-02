//
// Created by ngocq on 11/1/2020.
//

#ifndef COCCOC_MYLIBRARY_H
#define COCCOC_MYLIBRARY_H

extern std::map<int, int> ctg_cv(std::string id, std::string count);

class User{
private:
    std::string obj_id;
    std::map<int,int> ctg;
public:
    User();
    User(std::string obj, std::string ctg_id, std::string ctg_count){
        obj_id = obj;
        ctg = ctg_cv(ctg_id, ctg_count);
    }
    std::string p_objId(){
        return obj_id;
    }
    std::map<int,int> get_ctg(){
        return ctg;
    }
};

#endif //COCCOC_MYLIBRARY_H
