//
// Copyright 2017 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HD_ST_COMPUTE_SHADER_H
#define PXR_IMAGING_HD_ST_COMPUTE_SHADER_H

#include "pxr/pxr.h"
#include "pxr/imaging/hdSt/api.h"
#include "pxr/imaging/hd/version.h"
#include "pxr/imaging/hdSt/shaderCode.h"
#include "pxr/imaging/hd/bufferSource.h"

#include "pxr/imaging/garch/gl.h"

#include "pxr/usd/sdf/path.h"

#include "pxr/base/vt/value.h"
#include "pxr/base/tf/token.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

using HdStComputeShaderSharedPtr = std::shared_ptr<class HdStComputeShader>;

/// \class HdStComputeShader
///
/// A scene-based ComputeShader object.
///
/// When compute shaders are expressed in the scene graph, the HdSceneDelegate
/// can use this object to express these compute shaders in Storm.
/// In addition to the shader itself, a binding from the Computation Sprim
/// to the ComputeShader must be expressed as well.
class HdStComputeShader : public HdStShaderCode {
public:
    HDST_API
    HdStComputeShader();
    HDST_API
    virtual ~HdStComputeShader();


    // ---------------------------------------------------------------------- //
    /// \name HdShader Virtual Interface                                      //
    // ---------------------------------------------------------------------- //
    HDST_API
    virtual std::string GetSource(TfToken const &shaderStageKey) const;
    HDST_API
    virtual HdSt_MaterialParamVector const& GetParams() const;
    HDST_API
    virtual HdBufferArrayRangeSharedPtr const& GetShaderData() const;
    HDST_API
    virtual TextureDescriptorVector GetTextures() const;
    HDST_API
    virtual void BindResources(int program,
                               HdSt_ResourceBinder const &binder,
                               HdRenderPassState const &state) override;
    HDST_API
    virtual void UnbindResources(int program,
                                 HdSt_ResourceBinder const &binder,
                                 HdRenderPassState const &state) override;
    HDST_API
    virtual void AddBindings(HdBindingRequestVector *customBindings);
    HDST_API
    virtual ID ComputeHash() const;

    /// Setter method for prim
    HDST_API
    void SetComputeSource(const std::string &source);

    /// If the prim is based on asset, reload that asset.
    HDST_API
    virtual void Reload();

protected:
    HDST_API
    void _SetSource(TfToken const &shaderStageKey, std::string const &source);

private:
    std::string _computeSource;

    // Shader Parameters
    HdSt_MaterialParamVector _params;
    HdBufferSpecVector _paramSpec;
    HdBufferArrayRangeSharedPtr _paramArray;

    TextureDescriptorVector _textureDescriptors;
    
    // No copying
    HdStComputeShader(const HdStComputeShader &) = delete;
    HdStComputeShader &operator =(const HdStComputeShader &) = delete;
};


PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HD_ST_COMPUTE_SHADER_H
