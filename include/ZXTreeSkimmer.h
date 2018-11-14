#ifndef ZXTreeSkimmer_h
#define ZXTreeSkimmer_h

#include "TreeSkimmer.h"
#include "HZZTree.h"
//#include "Linkdef.h"

class ZXTreeSkimmer : public TreeSkimmer
{
    public:
        bool passSelection();
        void setTreeStatus(TTree* tree);
        void setTree(TTree* tree);
};

bool ZXTreeSkimmer::passSelection(){
    return passedZXCRSelection;
}

void ZXTreeSkimmer::setTreeStatus(TTree* tree){
    setTreeStatus(tree);
}

void ZXTreeSkimmer::setTree(TTree* tree){
    setTree(tree);
}
#endif
