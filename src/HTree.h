#pragma once

#include "HNode.h"
#include <string>
#include <vector>
#include "Global.h"

struct HNodePtr{

    HNode* node = nullptr;
    HNode* operator *();
    bool operator < (const HNodePtr& o) const;
    bool operator > (const HNodePtr& o) const;
    HNodePtr(HNode* node);
    HNodePtr();

};

class HTree{

    HNodePtr root;

    void visit_write_code(HNode*& node, CodeTable& code_table, Bitset code, int code_len);
    void find_furthest(HNode*& res);
    void visit_find_furthest(HNode* node, HNode*& furthest, int distance, int& max_distance);
    public:

    void construct_tree(std::vector<int>& freq_table);
    void get_codes_from_tree(CodeTable& code_table, Bitset& special);
    void print_tree(HNode* root);
    void create_code_table(CodeTable& code_table, std::vector<int> freq_table, Bitset& special);
};