/*
 * Copyright (C) 1997-2001, The University of Queensland
 * Copyright (C) 2001, Sun Microsystems, Inc
 * Copyright (C) 2002, Trent Waddington
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 *
 */

/*==============================================================================
 * FILE:       cfg.h
 * OVERVIEW:   Interface for a control flow graph, based on basic block nodes.
 *============================================================================*/

/*
 * $Revision: 1.20.2.2 $
 * 18 Apr 02 - Mike: Mods for boomerang
 * 04 Dec 02 - Mike: Added isJmpZ
 */

#ifndef _CFG_H_
#define _CFG_H_

#define COVERAGE 0      // Attempt to save memory

#include <stdio.h>      // For FILE
#include <list>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include "types.h"
#include "exp.h"        // For LocationSet

//#include "bitset.h"     // Saves time. Otherwise, any implementation file that
// defines say a BB, will need to #include this file

class Proc;
class UserProc;
class UseSet;
class DefSet;
class SSACounts;
class BinaryFile;
class BasicBlock;
typedef BasicBlock* PBB;
class HLLCode;
class HLCall;
class RTL;

#define BTHEN 0
#define BELSE 1

// an enumerated type for the class of stucture determined for a node
enum structType {
    Loop,      // Header of a loop only
    Cond,      // Header of a conditional only (if-then-else or switch)
    LoopCond,  // Header of a loop and a conditional
    Seq 	   // sequential statement (default)
};

// an type for the class of unstructured conditional jumps
enum unstructType {
    Structured,
    JumpInOutLoop,
    JumpIntoCase
};


// an enumerated type for the type of conditional headers
enum condType {
    IfThen,	    // conditional with only a then clause
    IfThenElse, // conditional with a then and an else clause
    IfElse,	    // conditional with only an else clause
    Case	    // nway conditional header (case statement)
};

// an enumerated type for the type of loop headers
enum loopType {
    PreTested,     // Header of a while loop
    PostTested,    // Header of a repeat loop
    Endless	       // Header of an endless loop
};

// Depth-first traversal constants.
enum travType {
    UNTRAVERSED,   // Initial value
    DFS_TAG,       // Remove redundant nodes pass
    DFS_LNUM,      // DFS loop stamping pass
    DFS_RNUM,      // DFS reverse loop stamping pass
    DFS_CASE,      // DFS case head tagging traversal
    DFS_PDOM,      // DFS post dominator ordering
    DFS_CODEGEN    // Code generating pass
};

// Kinds of basic block nodes
// reordering these will break the save files - trent
enum BBTYPE {
    ONEWAY,                  // unconditional branch
    TWOWAY,                  // conditional branch
    NWAY,                    // case branch
    CALL,                    // procedure call
    RET,                     // return
    FALL,                    // fall-through node
    COMPJUMP,                // computed jump
    COMPCALL,                // computed call
    INVALID                  // invalid instruction
};

enum SBBTYPE {
    NONE,					 // not structured
    PRETESTLOOP,			 // header of a loop
    POSTTESTLOOP,
    ENDLESSLOOP,
    JUMPINOUTLOOP,			 // an unstructured jump in or out of a loop
    JUMPINTOCASE,			 // an unstructured jump into a case statement
    IFGOTO,					 // unstructured conditional
    IFTHEN,				 	 // conditional with then clause
    IFTHENELSE,				 // conditional with then and else clauses
    IFELSE,					 // conditional with else clause only
    CASE					 // case statement (switch)
};

typedef std::list<PBB>::iterator BB_IT;
/*==============================================================================
 * BasicBlock class. <more comments>
 *============================================================================*/
class BasicBlock {
    /*
     * Objects of class Cfg can access the internals of a BasicBlock object.
     */
    friend class Cfg;

public:
    /*
     * Constructor.
     */
    BasicBlock();

    /*
     * Destructor.
     */
    ~BasicBlock();

    /*
     * Copy constructor.
     */
    BasicBlock(const BasicBlock& bb);

    /*
     * Return the type of the basic block.
     */
    BBTYPE getType();

    /*
     * Check if this BB has a label. If so, return the numeric value of
     * the label (nonzero integer). If not, returns zero.
     * See also Cfg::setLabel()
     */
    int getLabel();

    std::string &getLabelStr() {
        return m_labelStr;
    }
    void setLabelStr(std::string &s) {
        m_labelStr = s;
    }
    bool isLabelNeeded() {
        return m_labelneeded;
    }
    void setLabelNeeded(bool b) {
        m_labelneeded = b;
    }

    /*
     * Return whether this BB has been traversed or not
     */
    bool isTraversed();

    /*
     * Set the traversed flag
     */
    void setTraversed(bool bTraversed);

    /*
     * Print the BB. For -R and for debugging
     * Don't use = std::cout, because gdb doesn't know about std::
     */
    void print(std::ostream& os, bool withDF = false);
    char* prints();                     // For debugging

    /*
     * Set the type of the basic block.
     */
    void updateType(BBTYPE bbType, int iNumOutEdges);

    /*
     * Set the "jump reqd" bit. This means that this is an orphan BB (it is
     * generated, not part of the original program), and that the "fall through"
     * out edge (m_OutEdges[1]) has to be implemented as a jump. The back end
     * needs to take heed of this bit
     */
    void setJumpReqd();

    /*
     * Check if jump is required (see above).
     */
    bool isJumpReqd();

    /*
     * Adds an interprocedural out-edge to the basic block pBB that
     * represents this address.  The mapping between addresses and
     * basic blocks is done when the graph is well-formed.
     * Returns true if successful.
     */
    void addInterProcOutEdge(ADDRESS adr);
    bool addProcOutEdge (ADDRESS addr);

    /*
     * Get the address associated with the BB
     * Note that this is not always the same as getting the address
     * of the first RTL (e.g. if the first RTL is a delay instruction of
     * a DCTI instruction; then the address of this RTL will be 0)
     */
    ADDRESS getLowAddr();
    ADDRESS getHiAddr();

    /*
     * Get ptr to the list of RTLs.
     */
    std::list<RTL*>* getRTLs();

    /*
     * Get the set of in edges.
     */
    std::vector<PBB>& getInEdges();

    /*
     * Get the set of out edges.
     */
    std::vector<PBB>& getOutEdges();

    /*
     * Set an in edge to a new value; same number of in edges as before
     */
    void setInEdge(int i, PBB newIn);

    /*
     * Set an out edge to a new value; same number of out edges as before
     */
    void setOutEdge(int i, PBB newInEdge);

    /*
     * Get the n-th out edge or 0 if it does not exist
     */
    PBB getOutEdge(unsigned int i);

    /*
     * Add an in-edge
     */
    void addInEdge(PBB newInEdge);
    void deleteEdge(PBB edge);

    /*
     * Delete an in-edge
     */
    void deleteInEdge(std::vector<PBB>::iterator& it);
    void deleteInEdge(PBB edge);

    /*
     * If this is a call BB, find the fixed destination (if any)
     * Returns -1 otherwise
     */
    ADDRESS getCallDest();

    /*
     * Get the coverage (total number of bytes for this BB).
     */
    unsigned getCoverage();

    /*
     * Traverse this node and recurse on its children in a depth first manner.
     * Records the times at which this node was first visited and last visited.
     * Returns the number of nodes traversed.
     */
    unsigned DFTOrder(int& first, int& last);

    /*
     * Traverse this node and recurse on its parents in a reverse depth first manner.
     * Records the times at which this node was first visited and last visited.
     * Returns the number of nodes traversed.
     */
    unsigned RevDFTOrder(int& first, int& last);

    /*
     * Static comparison function that returns true if the first BB has an
     * address less than the second BB.
     */
    static bool lessAddress(PBB bb1, PBB bb2);

    /*
     * Static comparison function that returns true if the first BB has an
     * DFT first number less than the second BB.
     */
    static bool lessFirstDFT(PBB bb1, PBB bb2);

    /*
     * Static comparison function that returns true if the first BB has an
     * DFT last less than the second BB.
     */
    static bool lessLastDFT(PBB bb1, PBB bb2);

    /*
     * Resets the DFA sets of this BB.
     */
    void resetDFASets();

    /* get the condition */
    Exp *getCond();

    /* set the condition */
    void setCond(Exp *e);

    /* Check if there is a jump if equals relation */
    bool isJmpZ(PBB dest);

    /* get the loop body */
    BasicBlock *getLoopBody();

    /* Simplify all the expressions in this BB
     */
    void simplify();


    /*
     *  given an address, returns the outedge which corresponds to that address
     *  or 0 if there was no such outedge
     */

    PBB getCorrectOutEdge(ADDRESS a);

    /*
     * Depth first traversal of all bbs, numbering as we go and as we come back,
     * forward and reverse passes.  Use Cfg::establishDFTOrder() and
     * CFG::establishRevDFTOrder to create these values.
     */
    int         m_DFTfirst;        // depth-first traversal first visit
    int         m_DFTlast;         // depth-first traversal last visit
    int         m_DFTrevfirst;     // reverse depth-first traversal first visit
    int         m_DFTrevlast;      // reverse depth-first traversal last visit

#if 0
    BITSET& getPostDominatorSet() {
        return postdominators;
    }


    /*
     * The following are used for type analysis
     *
     * This function is use to gather and store the
     * use define chains for each register within
     * a basic block
     */
    void storeUseDefineStruct(BBBlock& inBlock);

    /*
     * Propagates type information between basic blocks
     * within a function
     */
    void propagateType(BasicBlock * prevBlock, bool endCase = false );

    /*
     * Used by propagate type to back track the
     * parent BB. The value of this variable is
     * meaningless otherwise
     */
    BasicBlock * tempPrevBB;
#endif

private:
    /*
     * Constructor. Called by Cfg::NewBB.
     */
    BasicBlock(std::list<RTL*>* pRtls, BBTYPE bbType, int iNumOutEdges);

    /*
     * Sets the RTLs for this BB. This is the only place that
     * the RTLs for a block must be set as we need to add the back
     * link for a call instruction to its enclosing BB.
     */
    void setRTLs(std::list<RTL*>* rtls);

#if 0
    /*
     * Build the sets of locations that reach to and propagate through this
     * basic block. Returns true if there was a change in the reach out set.
     */
    bool buildReachInOutSets(const BITSET* callDefines = NULL);
#endif

    // serialize the basic block
    bool serialize(std::ostream &ouf, int &len);

    // deserialize a basic block
    bool deserialize(std::istream &inf);

    // used during serialization
    std::vector<int> m_nOutEdges;     // numerical outedges
    int m_nindex;					// numerical index of this bb in list of bbs in CFG.

public:

    // code generation
    void generateBodyCode(HLLCode &hll, bool dup = false);

    /* high level structuring */
    SBBTYPE		m_structType;   // structured type of this node
    SBBTYPE		m_loopCondType;	// type of conditional to treat this loop header as (if any)
    PBB			m_loopHead;     // head of the most nested enclosing loop
    PBB			m_caseHead;		// head of the most nested enclosing case
    PBB			m_condFollow;	// follow of a conditional header
    PBB			m_loopFollow;	// follow of a loop header
    PBB			m_latchNode;	// latch node of a loop header

protected:
    /* general basic block information */
    BBTYPE          m_nodeType;     // type of basic block
    std::list<RTL*>*     m_pRtls;        // Ptr to list of RTLs
    int             m_iLabelNum;    // Nonzero if start of BB needs label
    std::string		m_labelStr;		// string label of this bb.
    bool			m_labelneeded;
    bool            m_bIncomplete;  // True if not yet complete
    bool            m_bJumpReqd;    // True if jump required for "fall through"

    /* in-edges and out-edges */
    std::vector<PBB>     m_InEdges;      // Vector of in-edges
    std::vector<PBB>     m_OutEdges;     // Vector of out-edges
    int             m_iNumInEdges;  // We need these two because GCC doesn't
    int             m_iNumOutEdges; // support resize() of vectors!

    /* for traversal */
    bool            m_iTraversed;   // traversal marker

public:

    /* stuff for data flow analysis */
    /* Reaching definitions: forward flow, any path */
    void getReachInAt(Statement *stmt, StatementSet &reachin);
    void getReachIn(StatementSet &reachin);
    void calcReachOut(StatementSet &reach);
    StatementSet &getReachOut() {
        return reachOut;
    }

    /* As above, for available definitions. These are used for the second
     * condition allowing copy propagation
     * Forward flow, all paths */
    void getAvailInAt(Statement *stmt, StatementSet &availin);
    void getAvailIn(StatementSet &availin);
    void calcAvailOut(StatementSet &avail);
    StatementSet &getAvailOut() {
        return availOut;
    }

    /* As above, for live locations. These are used for parameters and return
     * locations. Backwards flow, any path */
    void getLiveOutAt(Statement *stmt, LocationSet &liveout);
    void getLiveOut(LocationSet &liveout);
    void calcLiveIn(LocationSet &live);
    LocationSet &getLiveIn() {
        return liveIn;
    }

    /* set the return value */
    void setReturnVal(Exp *e);
    Exp *getReturnVal() {
        return m_returnVal;
    }

protected:
    // This is the set of statements whose definitions reach the end of this BB
    StatementSet reachOut;

    // This is the set of statements available (not redefined on any path)
    // at the end of this BB
    StatementSet availOut;

    // This is the set of locations that are upwardly exposed (not defined
    // along all paths from the start of the procedure to the statement)
    // at the start of the BB
    LocationSet liveIn;

    Exp* m_returnVal;

    /*
     * This field is used to test our assumption that the
     * substitution for a register in this BB is the same no matter
     * which entry to this BB is taken.
     */
    std::map<Exp*,Exp*> regSubs;

    /* Control flow analysis stuff, lifted from Doug Simon's honours thesis.
     */
    int ord;     // node's position within the ordering structure
    int revOrd;  // position within ordering structure for the reverse graph
    int inEdgesVisited;	// counts the number of in edges visited during a DFS
    int numForwardInEdges; // inedges to this node that aren't back edges
    int loopStamps[2], revLoopStamps[2]; // used for structuring analysis
    travType traversed;	// traversal flag for the numerous DFS's
    bool hllLabel; // emit a label for this node when generating HL code?
    char* labelStr; // the high level label for this node (if needed)
    int indentLevel; // the indentation level of this node in the final code

    // analysis information
    PBB immPDom; // immediate post dominator
    PBB loopHead; // head of the most nested enclosing loop
    PBB caseHead; // head of the most nested enclosing case
    PBB condFollow; // follow of a conditional header
    PBB loopFollow; // follow of a loop header
    PBB latchNode; // latching node of a loop header

    // Structured type of the node
    structType sType; // the structuring class (Loop, Cond , etc)
    unstructType usType; // the restructured type of a conditional header
    loopType lType; // the loop type of a loop header
    condType cType; // the conditional type of a conditional header

    void setLoopStamps(int &time, std::vector<PBB> &order);
    void setRevLoopStamps(int &time);
    void setRevOrder(std::vector<PBB> &order);

    void setLoopHead(PBB head) {
        loopHead = head;
    }
    PBB getLoopHead() {
        return loopHead;
    }
    void setLatchNode(PBB latch) {
        latchNode = latch;
    }
    bool isLatchNode() {
        return loopHead && loopHead->latchNode == this;
    }
    PBB getLatchNode() {
        return latchNode;
    }
    PBB getCaseHead() {
        return caseHead;
    }
    void setCaseHead(PBB head, PBB follow);

    structType getStructType() {
        return sType;
    }
    void setStructType(structType s);

    unstructType getUnstructType();
    void setUnstructType(unstructType us);

    loopType getLoopType();
    void setLoopType(loopType l);

    condType getCondType();
    void setCondType(condType l);

    void setLoopFollow(PBB other) {
        loopFollow = other;
    }
    PBB getLoopFollow() {
        return loopFollow;
    }

    void setCondFollow(PBB other) {
        condFollow = other;
    }
    PBB getCondFollow() {
        return condFollow;
    }

    // establish if this bb has a back edge to the given destination
    bool hasBackEdgeTo(BasicBlock *dest);

    // establish if this bb has any back edges leading FROM it
    bool hasBackEdge()
    {
        for (unsigned int i = 0; i < m_OutEdges.size(); i++)
            if (hasBackEdgeTo(m_OutEdges[i]))
                return true;
        return false;
    }

    // establish if this bb is an ancestor of another BB
    bool isAncestorOf(BasicBlock *other);

    bool inLoop(PBB header, PBB latch);

    bool isIn(std::list<PBB> &set, PBB bb)
    {
        for (std::list<PBB>::iterator it = set.begin();
                it != set.end(); it++)
            if (*it == bb) return true;
        return false;
    }

    char* indent(int indLevel, int extra = 0);
    bool allParentsGenerated();
    void emitGotoAndLabel(HLLCode *hll, int indLevel, PBB dest);
    void WriteBB(HLLCode *hll, int indLevel);

public:
    void generateCode(HLLCode *hll, int indLevel, PBB latch,
                      std::list<PBB> &followSet, std::list<PBB> &gotoSet);
};

// A type for the ADDRESS to BB map
typedef std::map<ADDRESS, PBB, std::less<ADDRESS> >   MAPBB;

/*==============================================================================
 * Control Flow Graph class. Contains all the BasicBlock objects for a
 * procedure. These BBs contain all the RTLs for the procedure, so by traversing
 * the Cfg, one traverses the whole procedure.
 *============================================================================*/
class Cfg {
public:
    /*
     * Constructor.
     */
    Cfg();

    /*
     * Destructor.
     */
    ~Cfg();

    /*
     * Set the pointer to the owning UserProc object
     */
    void setProc(UserProc* proc);

    /*
     * clear this CFG of all basic blocks, ready for decode
     */
    void clear();

    /*
     * Equality operator.
     */
    const Cfg& operator=(const Cfg& other); /* Copy constructor */

    /*
     * Checks to see if the address associated with pRtls is already
     * in the map as an incomplete BB; if so, it is completed now and
     * a pointer to that BB is returned. Otherwise,
     * allocates memory for a new basic block node, initializes its list
     * of RTLs with pRtls, its type to the given type, and allocates
     * enough space to hold pointers to the out-edges (based on given
     * numOutEdges).
     * The native address associated with the start of the BB is taken
     * from pRtls, and added to the map (unless 0).
     * NOTE: You cannot assume that the returned BB will have the RTL
     * associated with pStart as its first RTL, since the BB could be
     * split. You can however assume that the returned BB is suitable for
     * adding out edges (i.e. if the BB is split, you get the "bottom"
     * part of the BB, not the "top" (with lower addresses at the "top").
     * Returns NULL if not successful, or if there already exists a
     * completed BB at this address (this can happen with certain kinds of
     * forward branches).
     */
    PBB newBB ( std::list<RTL*>* pRtls, BBTYPE bbType, int iNumOutEdges);

    /*
     * Allocates space for a new, incomplete BB, and the given address is
     * added to the map. This BB will have to be completed before calling
     * WellFormCfg. This function will commonly be called via AddOutEdge()
     */
    PBB newIncompleteBB(ADDRESS addr);

    /*
     * Remove the incomplete BB at uAddr, if any. Was used when dealing
     * with the SKIP instruction, but no longer.
     */
    void removeIncBB(ADDRESS uAddr);

    /*
     * Adds an out-edge to the basic block pBB by filling in the first
     * slot that is empty.  Note: an address is given here; the out edge
     * will be filled in as a pointer to a BB. An incomplete BB will be
     * created if required. If bSetLabel is true, the destination BB will
     * have its "label required" bit set.
     */
    void addOutEdge(PBB pBB, ADDRESS adr, bool bSetLabel = false);

    /*
     * Adds an out-edge to the basic block pBB by filling in the first
     * slot that is empty.  Note: a pointer to a BB is given here.
     */
    void addOutEdge(PBB pBB, PBB pDestBB, bool bSetLabel = false);

    /*
     * Add a label for the given basicblock. The label number must be
     * a non-zero integer
     */
    void setLabel(PBB pBB);

    /*
     * Gets a pointer to the first BB this cfg. Also initialises `it' so
     * that calling GetNextBB will return the second BB, etc.
     * Also, *it is the first BB.
     * Returns 0 if there are no BBs this CFG.
     */
    PBB getFirstBB(BB_IT& it);

    /*
     * Gets a pointer to the next BB this cfg. `it' must be from a call to
     * GetFirstBB(), or from a subsequent call to GetNextBB().
     * Also, *it is the current BB.
     * Returns 0 if there are no more BBs this CFG.
     */
    PBB getNextBB(BB_IT& it);


    /*
     * Checks whether the given native address is a label (explicit or non
     * explicit) or not.  Explicit labels are addresses that have already
     * been tagged as being labels due to transfers of control to that
     * address.  Non explicit labels are those that belong to basic blocks
     * that have already been constructed (i.e. have previously been parsed)
     * and now need to be made explicit labels.  In the case of non explicit
     * labels, the basic block is split into two and types and edges are
     * adjusted accordingly. pNewBB is set to the lower part of the split BB.
     * Returns true if the native address is that of an explicit or non
     * explicit label, false otherwise.
     */
    bool label ( ADDRESS uNativeAddr, PBB& pNewBB );

    /*
     * Checks whether the given native address is in the map. If not,
     *  returns false. If so, returns true if it is incomplete.
     *  Otherwise, returns false.
     */
    bool isIncomplete ( ADDRESS uNativeAddr );

    /*
     * Just checks to see if the native address is a label. If not, the
     *  address is not added to the map of Lables to BBs.
     */
    bool isLabel ( ADDRESS uNativeAddr );

    /*
     * Sorts the BBs in the CFG according to the low address of each BB.
     * Useful because it makes printouts easier, if they used iterators
     * to traverse the list of BBs.
     */
    void sortByAddress ();

    /*
     * Sorts the BBs in the CFG by their first DFT numbers.
     */
    void sortByFirstDFT();

    /*
     * Sorts the BBs in the CFG by their last DFT numbers.
     */
    void sortByLastDFT();

    /*
     * Updates m_vectorBB to m_listBB
     */
    void updateVectorBB();

    /*
     * Transforms the input machine-dependent cfg, which has ADDRESS labels for
     * each out-edge, into a machine-independent cfg graph (i.e. a well-formed
     * graph) which has references to basic blocks for each out-edge.
     * Returns false if not successful.
     */
    bool wellFormCfg ( );

    /*
     * Given two basic blocks that belong to a well-formed graph, merges the
     * second block onto the first one and returns the new block.  The in and
     * out edges links are updated accordingly.
     * Note that two basic blocks can only be merged if each has a unique
     * out-edge and in-edge respectively, and these edges correspond to each
     * other.
     * Returns true if the blocks are merged.
     */
    bool mergeBBs ( PBB pb1, PBB pb2 );


    /*
     * Given a well-formed cfg graph, optimizations are performed on
     * the graph to reduce the number of basic blocks and edges.
     * Optimizations performed are: removal of branch chains (i.e. jumps
     * to jumps), removal of redundant jumps (i.e. jump to the next
     * instruction), merge basic blocks where possible, and remove
     * redundant basic blocks created by the previous optimizations.
     * Returns false if not successful.
     */
    bool compressCfg ( );


    /*
     * Given a well-formed cfg graph, a partial ordering is established between
     * the nodes. The ordering is based on the final visit to each node during a
     * depth first traversal such that if node n1 was visited for the last time
     * before node n2 was visited for the last time, n1 will be less than n2.
     * The return value indicates if all nodes where ordered. This will not be
     * the case for incomplete CFGs (e.g. switch table not completely
     * recognised) or where there are nodes unreachable from the entry node.
     */
    bool establishDFTOrder();

    /*
     * Performs establishDFTOrder on the inverse of the graph (ie, flips the graph)
     */
    bool establishRevDFTOrder();

    /*
     * Given a pointer to a basic block, return an index (e.g. 0 for the first
     * basic block, 1 for the next, ... n-1 for the last BB.
     */
    int pbbToIndex (PBB pBB);

    /*
     * Reset all the traversed flags.
     * To make this a useful public function, we need access to the
     * traversed flag with other public functions.
    */
    void unTraverse ( );

    /*
     * Return true if the CFG is well formed.
     */
    bool isWellFormed ( );

    /*
     * Return true if there is a BB at the address given whose first
     * RTL is an orphan, i.e. GetAddress() returns 0.
     */
    bool isOrphan ( ADDRESS uAddr);

    /*
     * This is called where a two-way branch is deleted, thereby joining
     * a two-way BB with it's successor. This happens for example when
     * transforming Intel floating point branches, and a branch on parity
     * is deleted. The joined BB becomes the type of the successor.
     * Returns true if succeeds.
     */
    bool joinBB( PBB pb1, PBB pb2);

    /*
     * Resets the DFA sets of all the BBs.
     */
    void resetDFASets();

    /*
     * Add a call to the set of calls within this procedure.
     */
    void addCall(HLCall* call);

    /*
     * Get the set of calls within this procedure.
     */
    std::set<HLCall*>& getCalls();

    /*
     * Replace all instances of search with replace.
     * Can be type sensitive if reqd
     */
    void searchAndReplace(Exp* search, Exp* replace);

    /*
     * Set the return value for this CFG
     * (assumes there is only one exit bb)
     */
    void setReturnVal(Exp *e);
    Exp *getReturnVal();

    /*
     * Structures the control flow graph
     */
    void structure();

    /*
     * Computes dominators for each BB.
     */
    void computeDominators();

    /*
     * Computes postdominators for each BB.
     */
    void computePostDominators();

    /*
     * Compute reaches/use information
     */
    void computeDataflow();
    void computeOnlyLiveness();
    void updateReaches();
    void updateAvail();
    void updateLiveness();
    void updateLiveEntryDefs();
    void clearLiveEntryDefsUsedby();
    // Summary information for this cfg
    StatementSet *getReachExit() {
        return (exitBB == NULL) ? NULL : &exitBB->reachOut;
    }
    StatementSet *getAvailExit() {
        return (exitBB == NULL) ? NULL : &exitBB->availOut;
    }
    LocationSet *getLiveEntry() {
        return (entryBB == NULL) ? NULL : &entryBB->liveIn;
    }

    /*
     * Virtual Function Call analysis
     */
    void virtualFunctionCalls(Prog* prog);

    std::vector<PBB> m_vectorBB; // faster access

    // serialize the CFG
    bool serialize(std::ostream &ouf, int &len);

    // deserialize a CFG
    bool deserialize(std::istream &inf);

    /* make the given BB into a call followed by a ret
     * and remove all the orphaned nodes.
     */
    void makeCallRet(PBB head, Proc *p);

    /* return a bb given an address */
    PBB bbForAddr(ADDRESS addr) {
        return m_mapBB[addr];
    }

    /* Simplify all the expressions in the CFG
     */
    void simplify();

private:

    /*
     * Split the given basic block at the RTL associated with uNativeAddr.
     * The first node's type becomes fall-through and ends at the
     * RTL prior to that associated with uNativeAddr.  The second node's
     * type becomes the type of the original basic block (pBB), and its
     * out-edges are those of the original basic block.
     * Precondition: assumes uNativeAddr is an address within the boundaries
     * of the given basic block.
     * If pNewBB is non zero, it is retained as the "bottom" part of the
     * split, i.e. splitBB just changes the "top" BB to not overlap the
     * existing one.
     * Returns a pointer to the "bottom" (new) part of the BB.
     */
    PBB splitBB (PBB pBB, ADDRESS uNativeAddr, PBB pNewBB = 0,
                 bool bDelRtls = false);

    /*
     * Completes the merge of pb1 and pb2 by adjusting out edges. No checks
     * are made that the merge is valid (hence this is a private function)
     * Deletes pb1 if bDelete is true
     */
    void completeMerge(PBB pb1, PBB pb2, bool bDelete);

    /*
     * checkEntryBB: emit error message if this pointer is null
     */
    bool checkEntryBB();

    /* Control flow analysis stuff, lifted from Doug Simon's honours thesis.
     */
    void setTimeStamps();
    PBB commonPDom(PBB curImmPDom, PBB succImmPDom);
    void findImmedPDom();
    void structConds();
    void structLoops();
    void checkConds();
    void determineLoopType(PBB header, bool* &loopNodes);
    void findLoopFollow(PBB header, bool* &loopNodes);
    void tagNodesInLoop(PBB header, bool* &loopNodes);

public:

    void removeUnneededLabels(HLLCode *hll);
    void generateDotFile(const char *str);

protected:

    /*
     * Pointer to the UserProc object that contains this CFG object
     */
    UserProc* myProc;

    /*
     * The list of pointers to BBs.
     */
    std::list<PBB> m_listBB;

    /*
     * Ordering of BBs for control flow structuring
     */
    std::vector<PBB> Ordering;
    std::vector<PBB> revOrdering;

    /*
     * All statements which reach the end of the ret bb.
     */
    StatementSet reachExit;

    /*
     * All statements which are available at the end of the ret bb
     * (not redefined on any path)
     */
    StatementSet availExit;

    /*
     * This is a pointer to a set of dummy statements defining locations that
     * are live on entry. This guarantees that every statement has a complete
     * set of definitions defining the locations it uses. This can be used
     * in canPropagateToAll()
     */
    StatementSet* liveEntryDefs;

    /*
     * The ADDRESS to PBB map.
     */
    MAPBB m_mapBB;

    /*
     * The entry and exit BBs.
     */
    BasicBlock* entryBB;
    BasicBlock* exitBB;

    /*
     * True if well formed.
     */
    bool m_bWellFormed;

    /*
     * Set of the call instructions in this procedure.
     */
    std::set<HLCall*> callSites;

    /*
     * Last label (positive integer) used by any BB this Cfg
     */
    int lastLabel;

public:
    /*
     * Get the entry-point or exit BB
     */
    PBB getEntryBB() {
        return entryBB;
    }
    PBB getExitBB()  {
        return exitBB;
    }

    /*
     * Set the entry-point BB (and exit BB as well)
     */
    void setEntryBB(PBB bb);

    PBB findRetNode();

    /*
     * Set an additional new out edge to a given value
     */
    void addNewOutEdge(PBB fromBB, PBB newOutEdge);

    /*
     * print this cfg, mainly for debugging
     */
    void print(std::ostream &out, bool withDF = false);

    /*
     * get the set of dummy Statements defining locations that are live on
     * entry to this proc
     */
    StatementSet *getLiveEntryDefs() {
        return liveEntryDefs;
    }

};              /* Cfg */

#endif
