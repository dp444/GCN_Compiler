#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

class FeatureExtractorPass : public PassInfoMixin<FeatureExtractorPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
        // Get the Loop Analysis results for this function
        LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);

        // --- 1. Map Blocks to IDs ---
        std::map<BasicBlock*, int> block_to_id;
        int block_id_counter = 0;
        for (BasicBlock &BB : F) {
            block_to_id[&BB] = block_id_counter++;
        }

        // --- 2. Extract Features (Nodes) ---
        for (BasicBlock &BB : F) {
            int arith_count = 0;
            int call_count = 0;
            int loop_depth = LI.getLoopDepth(&BB); // Get loop depth

            for (Instruction &I : BB) {
                // Check for arithmetic operations
                if (I.isBinaryOp()) { // Covers add, sub, mul, fadd, etc.
                    arith_count++;
                }
                // Check for call instructions
                else if (isa<CallInst>(I)) {
                    call_count++;
                }
            }
            
            // Print: "NODE:<block_id>,<feat1>,<feat2>,<feat3>"
            // We use outs() here, which prints to stdout.
            // If you want stderr, use errs()
            outs() << "NODE:" << block_to_id[&BB] << ","
                   << arith_count << ","
                   << loop_depth << ","
                   << call_count << "\n";
        }

        // --- 3. Extract Edges ---
        for (BasicBlock &BB : F) {
            const Instruction *terminator = BB.getTerminator();
            for (int i = 0; i < terminator->getNumSuccessors(); ++i) {
                BasicBlock *Succ = terminator->getSuccessor(i);
                
                if (block_to_id.count(Succ)) {
                    outs() << "EDGE:" << block_to_id[&BB] << ","
                           << block_to_id[Succ] << "\n";
                }
            }
        }

        return PreservedAnalyses::all();
    }

    static bool isRequired() { return true; }
};

// --- Boilerplate for registering the pass ---
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "FeatureExtractor", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "feature-extractor"){
            FPM.addPass(FeatureExtractorPass());
            return true;
          }
          return false;
        }
      );
      // We also need to register the LoopAnalysis pass
      PB.registerAnalysisRegistrationCallback(
        [](FunctionAnalysisManager &FAM) {
          // *** THIS IS THE CORRECTED LINE ***
          FAM.registerPass([&] { return LoopAnalysis(); });
        }
      );
    }
  };
}
