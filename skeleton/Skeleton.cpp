#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using PassPluginInfo = ::llvm::PassPluginLibraryInfo;

namespace {
    struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
        PreservedAnalyses run(Module& module, ModuleAnalysisManager& analysisManager) {
            for (auto& function: module) {
                for (auto& basicBlock : function) {
                    for (auto& instruction : basicBlock) {
                        auto* binaryOperator = dyn_cast<BinaryOperator>(&instruction);
                        if (binaryOperator != nullptr) {
                            IRBuilder<> builder(binaryOperator);
                            Value* lhs = binaryOperator->getOperand(0);
                            Value* rhs = binaryOperator->getOperand(1);
                            Value* timesOperator = builder.CreateMul(lhs, rhs);

                            for (auto& use : binaryOperator->uses()) {
                                User* user = use.getUser();
                                user->setOperand(use.getOperandNo(), timesOperator);
                            }
                        }
                    }
                }
            }

            return PreservedAnalyses::none();
        };
    };
}

extern "C" LLVM_ATTRIBUTE_WEAK
PassPluginInfo llvmGetPassPluginInfo() {
    auto passBuilderCallback = [](PassBuilder& PB) {
        auto epCallback = [](ModulePassManager& MPM, OptimizationLevel Level) {
            MPM.addPass(SkeletonPass());
        };
        PB.registerPipelineStartEPCallback(epCallback);
    };

    return
            {
                    .APIVersion = LLVM_PLUGIN_API_VERSION, .PluginName = "Skeleton pass", .PluginVersion = "v0.1", .RegisterPassBuilderCallbacks = passBuilderCallback
            };
}
