/*
 * Copyright 2019 Alex Andres
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "api/RTCDtmfSenderObserver.h"
#include "JavaClasses.h"
#include "JavaString.h"
#include "JavaUtils.h"
#include "JNI_WebRTC.h"

namespace jni
{
	RTCDtmfSenderObserver::RTCDtmfSenderObserver(JNIEnv * env, const JavaGlobalRef<jobject> & observer) :
		observer(observer),
		javaClass(JavaClasses::get<JavaRTCDtmfSenderObserverClass>(env))
	{
	}

	void RTCDtmfSenderObserver::OnToneChange(const std::string & tone, const std::string & tone_buffer)
	{
		JNIEnv * env = AttachCurrentThread();

		JavaLocalRef<jstring> jTone = JavaString::toJava(env, tone);
		JavaLocalRef<jstring> jToneBuffer = JavaString::toJava(env, tone_buffer);

		env->CallVoidMethod(observer, javaClass->onToneChange, jTone.get(), jToneBuffer.get());

		ExceptionCheck(env);
	}

	RTCDtmfSenderObserver::JavaRTCDtmfSenderObserverClass::JavaRTCDtmfSenderObserverClass(JNIEnv * env)
	{
		jclass cls = FindClass(env, PKG"RTCDtmfSenderObserver");

		onToneChange = GetMethod(env, cls, "onToneChange", "(Ljava/lang/String;Ljava/lang/String;)V");
	}
}