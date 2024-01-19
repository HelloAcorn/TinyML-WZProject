TINYML_HYGROPREDICT_TEST_SRCS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/hello_world_test.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/my_test_model.cc

TINYML_HYGROPREDICT_TEST_HDRS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/my_test_model.h

OUTPUT_HANDLER_TEST_SRCS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/output_handler_test.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/output_handler.cc

OUTPUT_HANDLER_TEST_HDRS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/output_handler.h \
tensorflow/lite/micro/examples/TinyML-HygroPredict/constants.h

TINYML_HYGROPREDICT_SRCS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/main.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/main_functions.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/my_test_model.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/output_handler.cc \
tensorflow/lite/micro/examples/TinyML-HygroPredict/constants.cc

TINYML_HYGROPREDICT_HDRS := \
tensorflow/lite/micro/examples/TinyML-HygroPredict/my_test_model.h \
tensorflow/lite/micro/examples/TinyML-HygroPredict/output_handler.h \
tensorflow/lite/micro/examples/TinyML-HygroPredict/constants.h \
tensorflow/lite/micro/examples/TinyML-HygroPredict/main_functions.h

#Find any platform - specific rules for this example.
include $(wildcard tensorflow/lite/micro/examples/TinyML-HygroPredict/*/Makefile.inc)

# Tests loading and running the sine model.
$(eval $(call microlite_test,tinyml_hygro_predict_test,\
$(TINYML_HYGROPREDICT_TEST_SRCS),$(TINYML_HYGROPREDICT_TEST_HDRS)))

# Tests producing an output.
$(eval $(call microlite_test,tinyml_hygro_predict_output_handler_test,\
$(TINYML_HYGROPREDICT_OUTPUT_HANDLER_TEST_SRCS),$(TINYML_HYGROPREDICT_OUTPUT_HANDLER_TEST_HDRS)))

# Builds a standalone binary.
$(eval $(call microlite_test,tinyml_hygro_predict,\
$(TINYML_HYGROPREDICT_SRCS),$(TINYML_HYGROPREDICT_HDRS)))
