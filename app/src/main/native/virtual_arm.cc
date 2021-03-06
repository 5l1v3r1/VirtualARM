//
// Created by 甘尧 on 2019-09-20.
//

#include <jni.h>
#include "virtual_arm.h"
#include "asm/arm64/instruction_decode.h"
#include "asm/arm64/cpu_arm64.h"
#include "frontend/ir/instruction_ir.h"
#include "dbi/arm64/dbi_visitor_arm64.h"


using namespace Instructions::A64;
using namespace CPU::A64;
using namespace Instructions::IR;


extern "C"
JNIEXPORT void JNICALL
load_test(JNIEnv *env, jobject instance) {
    FastBranchDecoder decoder;
//    InstrA64Ref instr = decoder.Decode(reinterpret_cast<InstrA64 *>((VAddr)rename + 24));
    assert(sizeof(Argument) == sizeof(Imm128));
    CPUContext context;
    context.cpu_registers[30].X = 0x111;
    assert(context.lr.X == 0x111);
}

static bool registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *jniMethods, int methods) {
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        return false;
    }
    return env->RegisterNatives(clazz, jniMethods, methods) >= 0;
}

static JNINativeMethod jniMethods[] = {
        {
                "launch",
                "()V",
                (void *) load_test
        }
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

    const char* CLASS_VIRTUAL_ARM = "com/swift/virtualarm/VirtualARM";

    int jniMethodSize = sizeof(JNINativeMethod);

    JNIEnv *env = nullptr;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    if (!registerNativeMethods(env, CLASS_VIRTUAL_ARM, jniMethods, sizeof(jniMethods) / jniMethodSize)) {
        return -1;
    }

    return JNI_VERSION_1_6;
}

