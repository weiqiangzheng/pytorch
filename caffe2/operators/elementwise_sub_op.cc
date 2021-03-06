#include "caffe2/operators/elementwise_sub_op.h"

namespace caffe2 {

REGISTER_CPU_OPERATOR(
    Sub,
    BinaryElementwiseOp<NumericTypes, CPUContext, SubFunctor<CPUContext>>);

#if !CAFFE2_MOBILE

REGISTER_CPU_OPERATOR(
    SubGradient,
    BinaryElementwiseGradientOp<
        NumericTypes,
        CPUContext,
        SubFunctor<CPUContext>>);

namespace {

class GetSubGradient final : public GradientMakerBase {
  using GradientMakerBase::GradientMakerBase;

  std::vector<OperatorDef> GetGradientDefs() override {
    return SingleGradientDef(
        "SubGradient",
        "",
        std::vector<std::string>{GO(0), I(0), I(1)},
        std::vector<std::string>{GI(0), GI(1)});
  }
};

} // namespace

REGISTER_GRADIENT(Sub, GetSubGradient);

#endif // !CAFFE2_MOBILE

} // namespace caffe2
