#include <sb6.h>

#include "kvmrt2_media_editor.h"
#include "qgleslcdcanvas.h"
#include <qdebug.h>
#include <math.h>
#include "newdisplaypool.h"

#define glCullFace		gl3wCullFace
#define glFrontFace		gl3wFrontFace
#define glHint		gl3wHint
#define glLineWidth		gl3wLineWidth
#define glPointSize		gl3wPointSize
#define glPolygonMode		gl3wPolygonMode
#define glScissor		gl3wScissor
#define glTexParameterf		gl3wTexParameterf
#define glTexParameterfv		gl3wTexParameterfv
#define glTexParameteri		gl3wTexParameteri
#define glTexParameteriv		gl3wTexParameteriv
#define glTexImage1D		gl3wTexImage1D
#define glTexImage2D		gl3wTexImage2D
#define glDrawBuffer		gl3wDrawBuffer
#define glClear		gl3wClear
#define glClearColor		gl3wClearColor
#define glClearStencil		gl3wClearStencil
#define glClearDepth		gl3wClearDepth
#define glStencilMask		gl3wStencilMask
#define glColorMask		gl3wColorMask
#define glDepthMask		gl3wDepthMask
#define glDisable		gl3wDisable
#define glEnable		gl3wEnable
#define glFinish		gl3wFinish
#define glFlush		gl3wFlush
#define glBlendFunc		gl3wBlendFunc
#define glLogicOp		gl3wLogicOp
#define glStencilFunc		gl3wStencilFunc
#define glStencilOp		gl3wStencilOp
#define glDepthFunc		gl3wDepthFunc
#define glPixelStoref		gl3wPixelStoref
#define glPixelStorei		gl3wPixelStorei
#define glReadBuffer		gl3wReadBuffer
#define glReadPixels		gl3wReadPixels
#define glGetBooleanv		gl3wGetBooleanv
#define glGetDoublev		gl3wGetDoublev
#define glGetError		gl3wGetError
#define glGetFloatv		gl3wGetFloatv
#define glGetIntegerv		gl3wGetIntegerv
#define glGetString		gl3wGetString
#define glGetTexImage		gl3wGetTexImage
#define glGetTexParameterfv		gl3wGetTexParameterfv
#define glGetTexParameteriv		gl3wGetTexParameteriv
#define glGetTexLevelParameterfv		gl3wGetTexLevelParameterfv
#define glGetTexLevelParameteriv		gl3wGetTexLevelParameteriv
#define glIsEnabled		gl3wIsEnabled
#define glDepthRange		gl3wDepthRange
#define glViewport		gl3wViewport
#define glDrawArrays		gl3wDrawArrays
#define glDrawElements		gl3wDrawElements
#define glGetPointerv		gl3wGetPointerv
#define glPolygonOffset		gl3wPolygonOffset
#define glCopyTexImage1D		gl3wCopyTexImage1D
#define glCopyTexImage2D		gl3wCopyTexImage2D
#define glCopyTexSubImage1D		gl3wCopyTexSubImage1D
#define glCopyTexSubImage2D		gl3wCopyTexSubImage2D
#define glTexSubImage1D		gl3wTexSubImage1D
#define glTexSubImage2D		gl3wTexSubImage2D
#define glBindTexture		gl3wBindTexture
#define glDeleteTextures		gl3wDeleteTextures
#define glGenTextures		gl3wGenTextures
#define glIsTexture		gl3wIsTexture
#define glBlendColor		gl3wBlendColor
#define glBlendEquation		gl3wBlendEquation
#define glDrawRangeElements		gl3wDrawRangeElements
#define glTexImage3D		gl3wTexImage3D
#define glTexSubImage3D		gl3wTexSubImage3D
#define glCopyTexSubImage3D		gl3wCopyTexSubImage3D
#define glActiveTexture		gl3wActiveTexture
#define glSampleCoverage		gl3wSampleCoverage
#define glCompressedTexImage3D		gl3wCompressedTexImage3D
#define glCompressedTexImage2D		gl3wCompressedTexImage2D
#define glCompressedTexImage1D		gl3wCompressedTexImage1D
#define glCompressedTexSubImage3D		gl3wCompressedTexSubImage3D
#define glCompressedTexSubImage2D		gl3wCompressedTexSubImage2D
#define glCompressedTexSubImage1D		gl3wCompressedTexSubImage1D
#define glGetCompressedTexImage		gl3wGetCompressedTexImage
#define glBlendFuncSeparate		gl3wBlendFuncSeparate
#define glMultiDrawArrays		gl3wMultiDrawArrays
#define glMultiDrawElements		gl3wMultiDrawElements
#define glPointParameterf		gl3wPointParameterf
#define glPointParameterfv		gl3wPointParameterfv
#define glPointParameteri		gl3wPointParameteri
#define glPointParameteriv		gl3wPointParameteriv
#define glGenQueries		gl3wGenQueries
#define glDeleteQueries		gl3wDeleteQueries
#define glIsQuery		gl3wIsQuery
#define glBeginQuery		gl3wBeginQuery
#define glEndQuery		gl3wEndQuery
#define glGetQueryiv		gl3wGetQueryiv
#define glGetQueryObjectiv		gl3wGetQueryObjectiv
#define glGetQueryObjectuiv		gl3wGetQueryObjectuiv
#define glBindBuffer		gl3wBindBuffer
#define glDeleteBuffers		gl3wDeleteBuffers
#define glGenBuffers		gl3wGenBuffers
#define glIsBuffer		gl3wIsBuffer
#define glBufferData		gl3wBufferData
#define glBufferSubData		gl3wBufferSubData
#define glGetBufferSubData		gl3wGetBufferSubData
#define glMapBuffer		gl3wMapBuffer
#define glUnmapBuffer		gl3wUnmapBuffer
#define glGetBufferParameteriv		gl3wGetBufferParameteriv
#define glGetBufferPointerv		gl3wGetBufferPointerv
#define glBlendEquationSeparate		gl3wBlendEquationSeparate
#define glDrawBuffers		gl3wDrawBuffers
#define glStencilOpSeparate		gl3wStencilOpSeparate
#define glStencilFuncSeparate		gl3wStencilFuncSeparate
#define glStencilMaskSeparate		gl3wStencilMaskSeparate
#define glAttachShader		gl3wAttachShader
#define glBindAttribLocation		gl3wBindAttribLocation
#define glCompileShader		gl3wCompileShader
#define glCreateProgram		gl3wCreateProgram
#define glCreateShader		gl3wCreateShader
#define glDeleteProgram		gl3wDeleteProgram
#define glDeleteShader		gl3wDeleteShader
#define glDetachShader		gl3wDetachShader
#define glDisableVertexAttribArray		gl3wDisableVertexAttribArray
#define glEnableVertexAttribArray		gl3wEnableVertexAttribArray
#define glGetActiveAttrib		gl3wGetActiveAttrib
#define glGetActiveUniform		gl3wGetActiveUniform
#define glGetAttachedShaders		gl3wGetAttachedShaders
#define glGetAttribLocation		gl3wGetAttribLocation
#define glGetProgramiv		gl3wGetProgramiv
#define glGetProgramInfoLog		gl3wGetProgramInfoLog
#define glGetShaderiv		gl3wGetShaderiv
#define glGetShaderInfoLog		gl3wGetShaderInfoLog
#define glGetShaderSource		gl3wGetShaderSource
#define glGetUniformLocation		gl3wGetUniformLocation
#define glGetUniformfv		gl3wGetUniformfv
#define glGetUniformiv		gl3wGetUniformiv
#define glGetVertexAttribdv		gl3wGetVertexAttribdv
#define glGetVertexAttribfv		gl3wGetVertexAttribfv
#define glGetVertexAttribiv		gl3wGetVertexAttribiv
#define glGetVertexAttribPointerv		gl3wGetVertexAttribPointerv
#define glIsProgram		gl3wIsProgram
#define glIsShader		gl3wIsShader
#define glLinkProgram		gl3wLinkProgram
#define glShaderSource		gl3wShaderSource
#define glUseProgram		gl3wUseProgram
#define glUniform1f		gl3wUniform1f
#define glUniform2f		gl3wUniform2f
#define glUniform3f		gl3wUniform3f
#define glUniform4f		gl3wUniform4f
#define glUniform1i		gl3wUniform1i
#define glUniform2i		gl3wUniform2i
#define glUniform3i		gl3wUniform3i
#define glUniform4i		gl3wUniform4i
#define glUniform1fv		gl3wUniform1fv
#define glUniform2fv		gl3wUniform2fv
#define glUniform3fv		gl3wUniform3fv
#define glUniform4fv		gl3wUniform4fv
#define glUniform1iv		gl3wUniform1iv
#define glUniform2iv		gl3wUniform2iv
#define glUniform3iv		gl3wUniform3iv
#define glUniform4iv		gl3wUniform4iv
#define glUniformMatrix2fv		gl3wUniformMatrix2fv
#define glUniformMatrix3fv		gl3wUniformMatrix3fv
#define glUniformMatrix4fv		gl3wUniformMatrix4fv
#define glValidateProgram		gl3wValidateProgram
#define glVertexAttrib1d		gl3wVertexAttrib1d
#define glVertexAttrib1dv		gl3wVertexAttrib1dv
#define glVertexAttrib1f		gl3wVertexAttrib1f
#define glVertexAttrib1fv		gl3wVertexAttrib1fv
#define glVertexAttrib1s		gl3wVertexAttrib1s
#define glVertexAttrib1sv		gl3wVertexAttrib1sv
#define glVertexAttrib2d		gl3wVertexAttrib2d
#define glVertexAttrib2dv		gl3wVertexAttrib2dv
#define glVertexAttrib2f		gl3wVertexAttrib2f
#define glVertexAttrib2fv		gl3wVertexAttrib2fv
#define glVertexAttrib2s		gl3wVertexAttrib2s
#define glVertexAttrib2sv		gl3wVertexAttrib2sv
#define glVertexAttrib3d		gl3wVertexAttrib3d
#define glVertexAttrib3dv		gl3wVertexAttrib3dv
#define glVertexAttrib3f		gl3wVertexAttrib3f
#define glVertexAttrib3fv		gl3wVertexAttrib3fv
#define glVertexAttrib3s		gl3wVertexAttrib3s
#define glVertexAttrib3sv		gl3wVertexAttrib3sv
#define glVertexAttrib4Nbv		gl3wVertexAttrib4Nbv
#define glVertexAttrib4Niv		gl3wVertexAttrib4Niv
#define glVertexAttrib4Nsv		gl3wVertexAttrib4Nsv
#define glVertexAttrib4Nub		gl3wVertexAttrib4Nub
#define glVertexAttrib4Nubv		gl3wVertexAttrib4Nubv
#define glVertexAttrib4Nuiv		gl3wVertexAttrib4Nuiv
#define glVertexAttrib4Nusv		gl3wVertexAttrib4Nusv
#define glVertexAttrib4bv		gl3wVertexAttrib4bv
#define glVertexAttrib4d		gl3wVertexAttrib4d
#define glVertexAttrib4dv		gl3wVertexAttrib4dv
#define glVertexAttrib4f		gl3wVertexAttrib4f
#define glVertexAttrib4fv		gl3wVertexAttrib4fv
#define glVertexAttrib4iv		gl3wVertexAttrib4iv
#define glVertexAttrib4s		gl3wVertexAttrib4s
#define glVertexAttrib4sv		gl3wVertexAttrib4sv
#define glVertexAttrib4ubv		gl3wVertexAttrib4ubv
#define glVertexAttrib4uiv		gl3wVertexAttrib4uiv
#define glVertexAttrib4usv		gl3wVertexAttrib4usv
#define glVertexAttribPointer		gl3wVertexAttribPointer
#define glUniformMatrix2x3fv		gl3wUniformMatrix2x3fv
#define glUniformMatrix3x2fv		gl3wUniformMatrix3x2fv
#define glUniformMatrix2x4fv		gl3wUniformMatrix2x4fv
#define glUniformMatrix4x2fv		gl3wUniformMatrix4x2fv
#define glUniformMatrix3x4fv		gl3wUniformMatrix3x4fv
#define glUniformMatrix4x3fv		gl3wUniformMatrix4x3fv
#define glColorMaski		gl3wColorMaski
#define glGetBooleani_v		gl3wGetBooleani_v
#define glGetIntegeri_v		gl3wGetIntegeri_v
#define glEnablei		gl3wEnablei
#define glDisablei		gl3wDisablei
#define glIsEnabledi		gl3wIsEnabledi
#define glBeginTransformFeedback		gl3wBeginTransformFeedback
#define glEndTransformFeedback		gl3wEndTransformFeedback
#define glBindBufferRange		gl3wBindBufferRange
#define glBindBufferBase		gl3wBindBufferBase
#define glTransformFeedbackVaryings		gl3wTransformFeedbackVaryings
#define glGetTransformFeedbackVarying		gl3wGetTransformFeedbackVarying
#define glClampColor		gl3wClampColor
#define glBeginConditionalRender		gl3wBeginConditionalRender
#define glEndConditionalRender		gl3wEndConditionalRender
#define glVertexAttribIPointer		gl3wVertexAttribIPointer
#define glGetVertexAttribIiv		gl3wGetVertexAttribIiv
#define glGetVertexAttribIuiv		gl3wGetVertexAttribIuiv
#define glVertexAttribI1i		gl3wVertexAttribI1i
#define glVertexAttribI2i		gl3wVertexAttribI2i
#define glVertexAttribI3i		gl3wVertexAttribI3i
#define glVertexAttribI4i		gl3wVertexAttribI4i
#define glVertexAttribI1ui		gl3wVertexAttribI1ui
#define glVertexAttribI2ui		gl3wVertexAttribI2ui
#define glVertexAttribI3ui		gl3wVertexAttribI3ui
#define glVertexAttribI4ui		gl3wVertexAttribI4ui
#define glVertexAttribI1iv		gl3wVertexAttribI1iv
#define glVertexAttribI2iv		gl3wVertexAttribI2iv
#define glVertexAttribI3iv		gl3wVertexAttribI3iv
#define glVertexAttribI4iv		gl3wVertexAttribI4iv
#define glVertexAttribI1uiv		gl3wVertexAttribI1uiv
#define glVertexAttribI2uiv		gl3wVertexAttribI2uiv
#define glVertexAttribI3uiv		gl3wVertexAttribI3uiv
#define glVertexAttribI4uiv		gl3wVertexAttribI4uiv
#define glVertexAttribI4bv		gl3wVertexAttribI4bv
#define glVertexAttribI4sv		gl3wVertexAttribI4sv
#define glVertexAttribI4ubv		gl3wVertexAttribI4ubv
#define glVertexAttribI4usv		gl3wVertexAttribI4usv
#define glGetUniformuiv		gl3wGetUniformuiv
#define glBindFragDataLocation		gl3wBindFragDataLocation
#define glGetFragDataLocation		gl3wGetFragDataLocation
#define glUniform1ui		gl3wUniform1ui
#define glUniform2ui		gl3wUniform2ui
#define glUniform3ui		gl3wUniform3ui
#define glUniform4ui		gl3wUniform4ui
#define glUniform1uiv		gl3wUniform1uiv
#define glUniform2uiv		gl3wUniform2uiv
#define glUniform3uiv		gl3wUniform3uiv
#define glUniform4uiv		gl3wUniform4uiv
#define glTexParameterIiv		gl3wTexParameterIiv
#define glTexParameterIuiv		gl3wTexParameterIuiv
#define glGetTexParameterIiv		gl3wGetTexParameterIiv
#define glGetTexParameterIuiv		gl3wGetTexParameterIuiv
#define glClearBufferiv		gl3wClearBufferiv
#define glClearBufferuiv		gl3wClearBufferuiv
#define glClearBufferfv		gl3wClearBufferfv
#define glClearBufferfi		gl3wClearBufferfi
#define glGetStringi		gl3wGetStringi
#define glDrawArraysInstanced		gl3wDrawArraysInstanced
#define glDrawElementsInstanced		gl3wDrawElementsInstanced
#define glTexBuffer		gl3wTexBuffer
#define glPrimitiveRestartIndex		gl3wPrimitiveRestartIndex
#define glGetInteger64i_v		gl3wGetInteger64i_v
#define glGetBufferParameteri64v		gl3wGetBufferParameteri64v
#define glFramebufferTexture		gl3wFramebufferTexture
#define glVertexAttribDivisor		gl3wVertexAttribDivisor
#define glMinSampleShading		gl3wMinSampleShading
#define glBlendEquationi		gl3wBlendEquationi
#define glBlendEquationSeparatei		gl3wBlendEquationSeparatei
#define glBlendFunci		gl3wBlendFunci
#define glBlendFuncSeparatei		gl3wBlendFuncSeparatei
#define glIsRenderbuffer		gl3wIsRenderbuffer
#define glBindRenderbuffer		gl3wBindRenderbuffer
#define glDeleteRenderbuffers		gl3wDeleteRenderbuffers
#define glGenRenderbuffers		gl3wGenRenderbuffers
#define glRenderbufferStorage		gl3wRenderbufferStorage
#define glGetRenderbufferParameteriv		gl3wGetRenderbufferParameteriv
#define glIsFramebuffer		gl3wIsFramebuffer
#define glBindFramebuffer		gl3wBindFramebuffer
#define glDeleteFramebuffers		gl3wDeleteFramebuffers
#define glGenFramebuffers		gl3wGenFramebuffers
#define glCheckFramebufferStatus		gl3wCheckFramebufferStatus
#define glFramebufferTexture1D		gl3wFramebufferTexture1D
#define glFramebufferTexture2D		gl3wFramebufferTexture2D
#define glFramebufferTexture3D		gl3wFramebufferTexture3D
#define glFramebufferRenderbuffer		gl3wFramebufferRenderbuffer
#define glGetFramebufferAttachmentParameteriv		gl3wGetFramebufferAttachmentParameteriv
#define glGenerateMipmap		gl3wGenerateMipmap
#define glBlitFramebuffer		gl3wBlitFramebuffer
#define glRenderbufferStorageMultisample		gl3wRenderbufferStorageMultisample
#define glFramebufferTextureLayer		gl3wFramebufferTextureLayer
#define glMapBufferRange		gl3wMapBufferRange
#define glFlushMappedBufferRange		gl3wFlushMappedBufferRange
#define glBindVertexArray		gl3wBindVertexArray
#define glDeleteVertexArrays		gl3wDeleteVertexArrays
#define glGenVertexArrays		gl3wGenVertexArrays
#define glIsVertexArray		gl3wIsVertexArray
#define glGetUniformIndices		gl3wGetUniformIndices
#define glGetActiveUniformsiv		gl3wGetActiveUniformsiv
#define glGetActiveUniformName		gl3wGetActiveUniformName
#define glGetUniformBlockIndex		gl3wGetUniformBlockIndex
#define glGetActiveUniformBlockiv		gl3wGetActiveUniformBlockiv
#define glGetActiveUniformBlockName		gl3wGetActiveUniformBlockName
#define glUniformBlockBinding		gl3wUniformBlockBinding
#define glCopyBufferSubData		gl3wCopyBufferSubData
#define glDrawElementsBaseVertex		gl3wDrawElementsBaseVertex
#define glDrawRangeElementsBaseVertex		gl3wDrawRangeElementsBaseVertex
#define glDrawElementsInstancedBaseVertex		gl3wDrawElementsInstancedBaseVertex
#define glMultiDrawElementsBaseVertex		gl3wMultiDrawElementsBaseVertex
#define glProvokingVertex		gl3wProvokingVertex
#define glFenceSync		gl3wFenceSync
#define glIsSync		gl3wIsSync
#define glDeleteSync		gl3wDeleteSync
#define glClientWaitSync		gl3wClientWaitSync
#define glWaitSync		gl3wWaitSync
#define glGetInteger64v		gl3wGetInteger64v
#define glGetSynciv		gl3wGetSynciv
#define glTexImage2DMultisample		gl3wTexImage2DMultisample
#define glTexImage3DMultisample		gl3wTexImage3DMultisample
#define glGetMultisamplefv		gl3wGetMultisamplefv
#define glSampleMaski		gl3wSampleMaski
#define glBlendEquationiARB		gl3wBlendEquationiARB
#define glBlendEquationSeparateiARB		gl3wBlendEquationSeparateiARB
#define glBlendFunciARB		gl3wBlendFunciARB
#define glBlendFuncSeparateiARB		gl3wBlendFuncSeparateiARB
#define glMinSampleShadingARB		gl3wMinSampleShadingARB
#define glNamedStringARB		gl3wNamedStringARB
#define glDeleteNamedStringARB		gl3wDeleteNamedStringARB
#define glCompileShaderIncludeARB		gl3wCompileShaderIncludeARB
#define glIsNamedStringARB		gl3wIsNamedStringARB
#define glGetNamedStringARB		gl3wGetNamedStringARB
#define glGetNamedStringivARB		gl3wGetNamedStringivARB
#define glBindFragDataLocationIndexed		gl3wBindFragDataLocationIndexed
#define glGetFragDataIndex		gl3wGetFragDataIndex
#define glGenSamplers		gl3wGenSamplers
#define glDeleteSamplers		gl3wDeleteSamplers
#define glIsSampler		gl3wIsSampler
#define glBindSampler		gl3wBindSampler
#define glSamplerParameteri		gl3wSamplerParameteri
#define glSamplerParameteriv		gl3wSamplerParameteriv
#define glSamplerParameterf		gl3wSamplerParameterf
#define glSamplerParameterfv		gl3wSamplerParameterfv
#define glSamplerParameterIiv		gl3wSamplerParameterIiv
#define glSamplerParameterIuiv		gl3wSamplerParameterIuiv
#define glGetSamplerParameteriv		gl3wGetSamplerParameteriv
#define glGetSamplerParameterIiv		gl3wGetSamplerParameterIiv
#define glGetSamplerParameterfv		gl3wGetSamplerParameterfv
#define glGetSamplerParameterIuiv		gl3wGetSamplerParameterIuiv
#define glQueryCounter		gl3wQueryCounter
#define glGetQueryObjecti64v		gl3wGetQueryObjecti64v
#define glGetQueryObjectui64v		gl3wGetQueryObjectui64v
#define glVertexP2ui		gl3wVertexP2ui
#define glVertexP2uiv		gl3wVertexP2uiv
#define glVertexP3ui		gl3wVertexP3ui
#define glVertexP3uiv		gl3wVertexP3uiv
#define glVertexP4ui		gl3wVertexP4ui
#define glVertexP4uiv		gl3wVertexP4uiv
#define glTexCoordP1ui		gl3wTexCoordP1ui
#define glTexCoordP1uiv		gl3wTexCoordP1uiv
#define glTexCoordP2ui		gl3wTexCoordP2ui
#define glTexCoordP2uiv		gl3wTexCoordP2uiv
#define glTexCoordP3ui		gl3wTexCoordP3ui
#define glTexCoordP3uiv		gl3wTexCoordP3uiv
#define glTexCoordP4ui		gl3wTexCoordP4ui
#define glTexCoordP4uiv		gl3wTexCoordP4uiv
#define glMultiTexCoordP1ui		gl3wMultiTexCoordP1ui
#define glMultiTexCoordP1uiv		gl3wMultiTexCoordP1uiv
#define glMultiTexCoordP2ui		gl3wMultiTexCoordP2ui
#define glMultiTexCoordP2uiv		gl3wMultiTexCoordP2uiv
#define glMultiTexCoordP3ui		gl3wMultiTexCoordP3ui
#define glMultiTexCoordP3uiv		gl3wMultiTexCoordP3uiv
#define glMultiTexCoordP4ui		gl3wMultiTexCoordP4ui
#define glMultiTexCoordP4uiv		gl3wMultiTexCoordP4uiv
#define glNormalP3ui		gl3wNormalP3ui
#define glNormalP3uiv		gl3wNormalP3uiv
#define glColorP3ui		gl3wColorP3ui
#define glColorP3uiv		gl3wColorP3uiv
#define glColorP4ui		gl3wColorP4ui
#define glColorP4uiv		gl3wColorP4uiv
#define glSecondaryColorP3ui		gl3wSecondaryColorP3ui
#define glSecondaryColorP3uiv		gl3wSecondaryColorP3uiv
#define glVertexAttribP1ui		gl3wVertexAttribP1ui
#define glVertexAttribP1uiv		gl3wVertexAttribP1uiv
#define glVertexAttribP2ui		gl3wVertexAttribP2ui
#define glVertexAttribP2uiv		gl3wVertexAttribP2uiv
#define glVertexAttribP3ui		gl3wVertexAttribP3ui
#define glVertexAttribP3uiv		gl3wVertexAttribP3uiv
#define glVertexAttribP4ui		gl3wVertexAttribP4ui
#define glVertexAttribP4uiv		gl3wVertexAttribP4uiv
#define glDrawArraysIndirect		gl3wDrawArraysIndirect
#define glDrawElementsIndirect		gl3wDrawElementsIndirect
#define glUniform1d		gl3wUniform1d
#define glUniform2d		gl3wUniform2d
#define glUniform3d		gl3wUniform3d
#define glUniform4d		gl3wUniform4d
#define glUniform1dv		gl3wUniform1dv
#define glUniform2dv		gl3wUniform2dv
#define glUniform3dv		gl3wUniform3dv
#define glUniform4dv		gl3wUniform4dv
#define glUniformMatrix2dv		gl3wUniformMatrix2dv
#define glUniformMatrix3dv		gl3wUniformMatrix3dv
#define glUniformMatrix4dv		gl3wUniformMatrix4dv
#define glUniformMatrix2x3dv		gl3wUniformMatrix2x3dv
#define glUniformMatrix2x4dv		gl3wUniformMatrix2x4dv
#define glUniformMatrix3x2dv		gl3wUniformMatrix3x2dv
#define glUniformMatrix3x4dv		gl3wUniformMatrix3x4dv
#define glUniformMatrix4x2dv		gl3wUniformMatrix4x2dv
#define glUniformMatrix4x3dv		gl3wUniformMatrix4x3dv
#define glGetUniformdv		gl3wGetUniformdv
#define glGetSubroutineUniformLocation		gl3wGetSubroutineUniformLocation
#define glGetSubroutineIndex		gl3wGetSubroutineIndex
#define glGetActiveSubroutineUniformiv		gl3wGetActiveSubroutineUniformiv
#define glGetActiveSubroutineUniformName		gl3wGetActiveSubroutineUniformName
#define glGetActiveSubroutineName		gl3wGetActiveSubroutineName
#define glUniformSubroutinesuiv		gl3wUniformSubroutinesuiv
#define glGetUniformSubroutineuiv		gl3wGetUniformSubroutineuiv
#define glGetProgramStageiv		gl3wGetProgramStageiv
#define glPatchParameteri		gl3wPatchParameteri
#define glPatchParameterfv		gl3wPatchParameterfv
#define glBindTransformFeedback		gl3wBindTransformFeedback
#define glDeleteTransformFeedbacks		gl3wDeleteTransformFeedbacks
#define glGenTransformFeedbacks		gl3wGenTransformFeedbacks
#define glIsTransformFeedback		gl3wIsTransformFeedback
#define glPauseTransformFeedback		gl3wPauseTransformFeedback
#define glResumeTransformFeedback		gl3wResumeTransformFeedback
#define glDrawTransformFeedback		gl3wDrawTransformFeedback
#define glDrawTransformFeedbackStream		gl3wDrawTransformFeedbackStream
#define glBeginQueryIndexed		gl3wBeginQueryIndexed
#define glEndQueryIndexed		gl3wEndQueryIndexed
#define glGetQueryIndexediv		gl3wGetQueryIndexediv
#define glReleaseShaderCompiler		gl3wReleaseShaderCompiler
#define glShaderBinary		gl3wShaderBinary
#define glGetShaderPrecisionFormat		gl3wGetShaderPrecisionFormat
#define glDepthRangef		gl3wDepthRangef
#define glClearDepthf		gl3wClearDepthf
#define glGetProgramBinary		gl3wGetProgramBinary
#define glProgramBinary		gl3wProgramBinary
#define glProgramParameteri		gl3wProgramParameteri
#define glUseProgramStages		gl3wUseProgramStages
#define glActiveShaderProgram		gl3wActiveShaderProgram
#define glCreateShaderProgramv		gl3wCreateShaderProgramv
#define glBindProgramPipeline		gl3wBindProgramPipeline
#define glDeleteProgramPipelines		gl3wDeleteProgramPipelines
#define glGenProgramPipelines		gl3wGenProgramPipelines
#define glIsProgramPipeline		gl3wIsProgramPipeline
#define glGetProgramPipelineiv		gl3wGetProgramPipelineiv
#define glProgramUniform1i		gl3wProgramUniform1i
#define glProgramUniform1iv		gl3wProgramUniform1iv
#define glProgramUniform1f		gl3wProgramUniform1f
#define glProgramUniform1fv		gl3wProgramUniform1fv
#define glProgramUniform1d		gl3wProgramUniform1d
#define glProgramUniform1dv		gl3wProgramUniform1dv
#define glProgramUniform1ui		gl3wProgramUniform1ui
#define glProgramUniform1uiv		gl3wProgramUniform1uiv
#define glProgramUniform2i		gl3wProgramUniform2i
#define glProgramUniform2iv		gl3wProgramUniform2iv
#define glProgramUniform2f		gl3wProgramUniform2f
#define glProgramUniform2fv		gl3wProgramUniform2fv
#define glProgramUniform2d		gl3wProgramUniform2d
#define glProgramUniform2dv		gl3wProgramUniform2dv
#define glProgramUniform2ui		gl3wProgramUniform2ui
#define glProgramUniform2uiv		gl3wProgramUniform2uiv
#define glProgramUniform3i		gl3wProgramUniform3i
#define glProgramUniform3iv		gl3wProgramUniform3iv
#define glProgramUniform3f		gl3wProgramUniform3f
#define glProgramUniform3fv		gl3wProgramUniform3fv
#define glProgramUniform3d		gl3wProgramUniform3d
#define glProgramUniform3dv		gl3wProgramUniform3dv
#define glProgramUniform3ui		gl3wProgramUniform3ui
#define glProgramUniform3uiv		gl3wProgramUniform3uiv
#define glProgramUniform4i		gl3wProgramUniform4i
#define glProgramUniform4iv		gl3wProgramUniform4iv
#define glProgramUniform4f		gl3wProgramUniform4f
#define glProgramUniform4fv		gl3wProgramUniform4fv
#define glProgramUniform4d		gl3wProgramUniform4d
#define glProgramUniform4dv		gl3wProgramUniform4dv
#define glProgramUniform4ui		gl3wProgramUniform4ui
#define glProgramUniform4uiv		gl3wProgramUniform4uiv
#define glProgramUniformMatrix2fv		gl3wProgramUniformMatrix2fv
#define glProgramUniformMatrix3fv		gl3wProgramUniformMatrix3fv
#define glProgramUniformMatrix4fv		gl3wProgramUniformMatrix4fv
#define glProgramUniformMatrix2dv		gl3wProgramUniformMatrix2dv
#define glProgramUniformMatrix3dv		gl3wProgramUniformMatrix3dv
#define glProgramUniformMatrix4dv		gl3wProgramUniformMatrix4dv
#define glProgramUniformMatrix2x3fv		gl3wProgramUniformMatrix2x3fv
#define glProgramUniformMatrix3x2fv		gl3wProgramUniformMatrix3x2fv
#define glProgramUniformMatrix2x4fv		gl3wProgramUniformMatrix2x4fv
#define glProgramUniformMatrix4x2fv		gl3wProgramUniformMatrix4x2fv
#define glProgramUniformMatrix3x4fv		gl3wProgramUniformMatrix3x4fv
#define glProgramUniformMatrix4x3fv		gl3wProgramUniformMatrix4x3fv
#define glProgramUniformMatrix2x3dv		gl3wProgramUniformMatrix2x3dv
#define glProgramUniformMatrix3x2dv		gl3wProgramUniformMatrix3x2dv
#define glProgramUniformMatrix2x4dv		gl3wProgramUniformMatrix2x4dv
#define glProgramUniformMatrix4x2dv		gl3wProgramUniformMatrix4x2dv
#define glProgramUniformMatrix3x4dv		gl3wProgramUniformMatrix3x4dv
#define glProgramUniformMatrix4x3dv		gl3wProgramUniformMatrix4x3dv
#define glValidateProgramPipeline		gl3wValidateProgramPipeline
#define glGetProgramPipelineInfoLog		gl3wGetProgramPipelineInfoLog
#define glVertexAttribL1d		gl3wVertexAttribL1d
#define glVertexAttribL2d		gl3wVertexAttribL2d
#define glVertexAttribL3d		gl3wVertexAttribL3d
#define glVertexAttribL4d		gl3wVertexAttribL4d
#define glVertexAttribL1dv		gl3wVertexAttribL1dv
#define glVertexAttribL2dv		gl3wVertexAttribL2dv
#define glVertexAttribL3dv		gl3wVertexAttribL3dv
#define glVertexAttribL4dv		gl3wVertexAttribL4dv
#define glVertexAttribLPointer		gl3wVertexAttribLPointer
#define glGetVertexAttribLdv		gl3wGetVertexAttribLdv
#define glViewportArrayv		gl3wViewportArrayv
#define glViewportIndexedf		gl3wViewportIndexedf
#define glViewportIndexedfv		gl3wViewportIndexedfv
#define glScissorArrayv		gl3wScissorArrayv
#define glScissorIndexed		gl3wScissorIndexed
#define glScissorIndexedv		gl3wScissorIndexedv
#define glDepthRangeArrayv		gl3wDepthRangeArrayv
#define glDepthRangeIndexed		gl3wDepthRangeIndexed
#define glGetFloati_v		gl3wGetFloati_v
#define glGetDoublei_v		gl3wGetDoublei_v
#define glCreateSyncFromCLeventARB		gl3wCreateSyncFromCLeventARB
#define glDebugMessageControlARB		gl3wDebugMessageControlARB
#define glDebugMessageInsertARB		gl3wDebugMessageInsertARB
#define glDebugMessageCallbackARB		gl3wDebugMessageCallbackARB
#define glGetDebugMessageLogARB		gl3wGetDebugMessageLogARB
#define glGetGraphicsResetStatusARB		gl3wGetGraphicsResetStatusARB
#define glGetnMapdvARB		gl3wGetnMapdvARB
#define glGetnMapfvARB		gl3wGetnMapfvARB
#define glGetnMapivARB		gl3wGetnMapivARB
#define glGetnPixelMapfvARB		gl3wGetnPixelMapfvARB
#define glGetnPixelMapuivARB		gl3wGetnPixelMapuivARB
#define glGetnPixelMapusvARB		gl3wGetnPixelMapusvARB
#define glGetnPolygonStippleARB		gl3wGetnPolygonStippleARB
#define glGetnColorTableARB		gl3wGetnColorTableARB
#define glGetnConvolutionFilterARB		gl3wGetnConvolutionFilterARB
#define glGetnSeparableFilterARB		gl3wGetnSeparableFilterARB
#define glGetnHistogramARB		gl3wGetnHistogramARB
#define glGetnMinmaxARB		gl3wGetnMinmaxARB
#define glGetnTexImageARB		gl3wGetnTexImageARB
#define glReadnPixelsARB		gl3wReadnPixelsARB
#define glGetnCompressedTexImageARB		gl3wGetnCompressedTexImageARB
#define glGetnUniformfvARB		gl3wGetnUniformfvARB
#define glGetnUniformivARB		gl3wGetnUniformivARB
#define glGetnUniformuivARB		gl3wGetnUniformuivARB
#define glGetnUniformdvARB		gl3wGetnUniformdvARB
#define glDrawArraysInstancedBaseInstance		gl3wDrawArraysInstancedBaseInstance
#define glDrawElementsInstancedBaseInstance		gl3wDrawElementsInstancedBaseInstance
#define glDrawElementsInstancedBaseVertexBaseInstance		gl3wDrawElementsInstancedBaseVertexBaseInstance
#define glDrawTransformFeedbackInstanced		gl3wDrawTransformFeedbackInstanced
#define glDrawTransformFeedbackStreamInstanced		gl3wDrawTransformFeedbackStreamInstanced
#define glGetInternalformativ		gl3wGetInternalformativ
#define glGetActiveAtomicCounterBufferiv		gl3wGetActiveAtomicCounterBufferiv
#define glBindImageTexture		gl3wBindImageTexture
#define glMemoryBarrier		gl3wMemoryBarrier
#define glTexStorage1D		gl3wTexStorage1D
#define glTexStorage2D		gl3wTexStorage2D
#define glTexStorage3D		gl3wTexStorage3D
#define glTextureStorage1DEXT		gl3wTextureStorage1DEXT
#define glTextureStorage2DEXT		gl3wTextureStorage2DEXT
#define glTextureStorage3DEXT		gl3wTextureStorage3DEXT
#define glDebugMessageControl		gl3wDebugMessageControl
#define glDebugMessageInsert		gl3wDebugMessageInsert
#define glDebugMessageCallback		gl3wDebugMessageCallback
#define glGetDebugMessageLog		gl3wGetDebugMessageLog
#define glPushDebugGroup		gl3wPushDebugGroup
#define glPopDebugGroup		gl3wPopDebugGroup
#define glObjectLabel		gl3wObjectLabel
#define glGetObjectLabel		gl3wGetObjectLabel
#define glObjectPtrLabel		gl3wObjectPtrLabel
#define glGetObjectPtrLabel		gl3wGetObjectPtrLabel
#define glClearBufferData		gl3wClearBufferData
#define glClearBufferSubData		gl3wClearBufferSubData
#define glClearNamedBufferDataEXT		gl3wClearNamedBufferDataEXT
#define glClearNamedBufferSubDataEXT		gl3wClearNamedBufferSubDataEXT
#define glDispatchCompute		gl3wDispatchCompute
#define glDispatchComputeIndirect		gl3wDispatchComputeIndirect
#define glCopyImageSubData		gl3wCopyImageSubData
#define glTextureView		gl3wTextureView
#define glBindVertexBuffer		gl3wBindVertexBuffer
#define glVertexAttribFormat		gl3wVertexAttribFormat
#define glVertexAttribIFormat		gl3wVertexAttribIFormat
#define glVertexAttribLFormat		gl3wVertexAttribLFormat
#define glVertexAttribBinding		gl3wVertexAttribBinding
#define glVertexBindingDivisor		gl3wVertexBindingDivisor
#define glVertexArrayBindVertexBufferEXT		gl3wVertexArrayBindVertexBufferEXT
#define glVertexArrayVertexAttribFormatEXT		gl3wVertexArrayVertexAttribFormatEXT
#define glVertexArrayVertexAttribIFormatEXT		gl3wVertexArrayVertexAttribIFormatEXT
#define glVertexArrayVertexAttribLFormatEXT		gl3wVertexArrayVertexAttribLFormatEXT
#define glVertexArrayVertexAttribBindingEXT		gl3wVertexArrayVertexAttribBindingEXT
#define glVertexArrayVertexBindingDivisorEXT		gl3wVertexArrayVertexBindingDivisorEXT
#define glFramebufferParameteri		gl3wFramebufferParameteri
#define glGetFramebufferParameteriv		gl3wGetFramebufferParameteriv
#define glNamedFramebufferParameteriEXT		gl3wNamedFramebufferParameteriEXT
#define glGetNamedFramebufferParameterivEXT		gl3wGetNamedFramebufferParameterivEXT
#define glGetInternalformati64v		gl3wGetInternalformati64v
#define glInvalidateTexSubImage		gl3wInvalidateTexSubImage
#define glInvalidateTexImage		gl3wInvalidateTexImage
#define glInvalidateBufferSubData		gl3wInvalidateBufferSubData
#define glInvalidateBufferData		gl3wInvalidateBufferData
#define glInvalidateFramebuffer		gl3wInvalidateFramebuffer
#define glInvalidateSubFramebuffer		gl3wInvalidateSubFramebuffer
#define glMultiDrawArraysIndirect		gl3wMultiDrawArraysIndirect
#define glMultiDrawElementsIndirect		gl3wMultiDrawElementsIndirect
#define glGetProgramInterfaceiv		gl3wGetProgramInterfaceiv
#define glGetProgramResourceIndex		gl3wGetProgramResourceIndex
#define glGetProgramResourceName		gl3wGetProgramResourceName
#define glGetProgramResourceiv		gl3wGetProgramResourceiv
#define glGetProgramResourceLocation		gl3wGetProgramResourceLocation
#define glGetProgramResourceLocationIndex		gl3wGetProgramResourceLocationIndex
#define glShaderStorageBlockBinding		gl3wShaderStorageBlockBinding
#define glTexBufferRange		gl3wTexBufferRange
#define glTextureBufferRangeEXT		gl3wTextureBufferRangeEXT
#define glTexStorage2DMultisample		gl3wTexStorage2DMultisample
#define glTexStorage3DMultisample		gl3wTexStorage3DMultisample
#define glTextureStorage2DMultisampleEXT		gl3wTextureStorage2DMultisampleEXT
#define glTextureStorage3DMultisampleEXT		gl3wTextureStorage3DMultisampleEXT

#define MAIN_WINDOW kvmrt2_media_editor

GLuint compile_shaders(void)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;

	static const GLchar * vertexShaderSrc[] =
	{
		"#version 430 core\n"
		"layout (location = 0) in vec4 offset;\n"
		"layout (location = 1) in vec4 color;\n"
		"out VS_OUT\n"
		"{ vec4 color; } vs_out;\n"
		"out vec4 vs_color;\n"
		"void main(void)\n"
		"{\n"
		"const vec4 vertices[3] = vec4[3]("
		"vec4(0.25, -0.25, 0.5, 1.0),"
		"vec4(-0.25, -0.25, 0.5, 1.0),"
		"vec4(0.25, 0.25, 0.5, 1.0));\n"
		"gl_Position = vertices[gl_VertexID] + offset;\n"
		"vs_out.color = color;"
		"}"

	};

	static const GLchar * fragShaderSrc[] =
	{
		"#version 430 core\n"
		"in VS_OUT\n"
		"{ vec4 color; } fs_in;\n"
		"out vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"color = fs_in.color;\n"
		"}"
	};

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragShaderSrc, nullptr);
	glCompileShader(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

class my_app : public sb6::application
{
public:
	void startup()
	{
		program = compile_shaders();
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
	}
	void render(double currentTime)
	{
		float r = (float)sin(currentTime)*0.5f;
		float g = (float)cos(currentTime)*0.5f;
		float b = 0.0f;
		float a = 1.0f;

		const GLfloat col[] = { r, g, b, a };
		//const GLfloat col[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, col);
		glUseProgram(program);
		
		GLfloat attrib[] = {
			(float)sin(currentTime) * 0.5f,
			(float)cos(currentTime) * 0.5f,
			0.0f, 0.0f
		};

		glVertexAttrib4fv(0, attrib);

		//glDrawArrays(GL_POINTS, 0, 1);
		//glPointSize(40.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		qDebug() << Q_FUNC_INFO << currentTime << r << g << b << a;
	}

private:
	GLuint program;
	GLuint vao;
};

sb6::application *app = 0;

void MAIN_WINDOW::betaInit()
{
	connect(ui.actionNew, &QAction::triggered, [this]()
	{
		NewDisplayPool dlg(this);
		if (dlg.exec())
		{
		
		}
	});

	connect(ui.actionLoad, &QAction::triggered, [this]()
	{
		my_app *app = new my_app;
		app->run(app);
		delete app;
	});
}

/*
#if defined _WIN32
#define DECLARE_MAIN(a)                             \
sb6::application *app = 0;                          \
int CALLBACK WinMain(HINSTANCE hInstance,           \
HINSTANCE hPrevInstance,       \
LPSTR lpCmdLine,               \
int nCmdShow)                  \
{                                                   \
a *app = new a;                                 \
app->run(app);                                  \
delete app;                                     \
return 0;                                       \
}
#elif defined _LINUX || defined __APPLE__
#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
a *app = new a;                                 \
app->run(app);                                  \
delete app;                                     \
return 0;                                       \
}
#else
*/