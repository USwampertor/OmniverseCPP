//
// Copyright 2018 Pixar
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

#ifndef PXR_USD_SDR_SHADER_NODE_H
#define PXR_USD_SDR_SHADER_NODE_H

/// \file sdr/shaderNode.h

#include "pxr/pxr.h"
#include "pxr/usd/sdr/api.h"
#include "pxr/base/tf/staticTokens.h"
#include "pxr/usd/ndr/node.h"
#include "pxr/usd/sdr/declare.h"

PXR_NAMESPACE_OPEN_SCOPE

// Note: Metadata keys that are generated by parsers should start with
// "__SDR__" to reduce the risk of collision with metadata actually in the
// shader.
#define SDR_NODE_METADATA_TOKENS   \
    ((Category, "category"))       \
    ((Role, "role"))               \
    ((Departments, "departments")) \
    ((Help, "help"))               \
    ((Label, "label"))             \
    ((Pages, "pages"))             \
    ((Primvars, "primvars"))       \
    ((ImplementationName, "__SDR__implementationName"))\
    ((Target, "__SDR__target"))

// Note: The concept of context is defined on NdrNode and can be queried with
// the GetContext() method. Sdr categorizes shaders by the context in which they
// are used inside of a renderer. For instance during 'pattern' evaluation to
// feed into a surface or volume shader. For BXDFs used in 'surface' and
// 'volume' rendering situations.
#define SDR_NODE_CONTEXT_TOKENS      \
    ((Pattern, "pattern"))           \
    ((Surface, "surface"))           \
    ((Volume, "volume"))             \
    ((Displacement, "displacement")) \
    ((Light, "light"))               \
    ((LightFilter, "lightFilter"))   \
    ((SampleFilter, "sampleFilter")) \
    ((PixelFilter, "pixelFilter"))

#define SDR_NODE_ROLE_TOKENS         \
    ((Primvar, "primvar"))           \
    ((Texture, "texture"))           \
    ((Field, "field"))               \
    ((Math, "math"))                 \

TF_DECLARE_PUBLIC_TOKENS(SdrNodeMetadata, SDR_API, SDR_NODE_METADATA_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(SdrNodeContext, SDR_API, SDR_NODE_CONTEXT_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(SdrNodeRole, SDR_API, SDR_NODE_ROLE_TOKENS);

/// \class SdrShaderNode
///
/// A specialized version of `NdrNode` which holds shading information.
///
class SdrShaderNode : public NdrNode
{
public:
    /// Constructor.
    SDR_API
    SdrShaderNode(const NdrIdentifier& identifier,
                  const NdrVersion& version,
                  const std::string& name,
                  const TfToken& family,
                  const TfToken& context,
                  const TfToken& sourceType,
                  const std::string& definitionURI,
                  const std::string& implementationURI,
                  NdrPropertyUniquePtrVec&& properties,
                  const NdrTokenMap& metadata = NdrTokenMap(),
                  const std::string &sourceCode = std::string());

    /// \name Inputs and Outputs
    /// An input or output is also generically referred to as a "property".
    /// @{

    /// Get a shader input property by name. `nullptr` is returned if an input
    /// with the given name does not exist.
    SDR_API
    SdrShaderPropertyConstPtr GetShaderInput(const TfToken& inputName) const;

    /// Get a shader output property by name. `nullptr` is returned if an output
    /// with the given name does not exist.
    SDR_API
    SdrShaderPropertyConstPtr GetShaderOutput(const TfToken& outputName) const;

    /// Returns the list of all inputs that are tagged as asset identifier 
    /// inputs.
    SDR_API
    NdrTokenVec GetAssetIdentifierInputNames() const;

    /// Returns the first shader input that is tagged as the default input.
    /// A default input and its value can be used to acquire a fallback value
    /// for a node when the node is considered 'disabled' or otherwise
    /// incapable of producing an output value.
    SDR_API
    SdrShaderPropertyConstPtr GetDefaultInput() const;

    /// @}


    /// \name Metadata
    /// The metadata returned here is a direct result of what the parser plugin
    /// is able to determine about the node. See the documentation for a
    /// specific parser plugin to get help on what the parser is looking for to
    /// populate these values.
    /// @{

    /// The label assigned to this node, if any. Distinct from the name
    /// returned from `GetName()`. In the context of a UI, the label value
    /// might be used as the display name for the node instead of the name.
    SDR_API
    const TfToken& GetLabel() const { return _label; }

    /// The category assigned to this node, if any. Distinct from the family
    /// returned from `GetFamily()`.
    SDR_API
    const TfToken& GetCategory() const { return _category; }

    /// Returns the role of this node. This is used to annotate the role that 
    /// the shader node plays inside a shader network. We can tag certain
    /// shaders to indicate their role within a shading network. We currently
    /// tag primvar reading nodes, texture reading nodes and nodes that access
    /// volume fields (like extinction or scattering). This is done to identify
    /// resources used by a shading network.
    SDR_API
    const std::string &GetRole() const;

    /// The help message assigned to this node, if any.
    SDR_API
    const std::string& GetHelp() const;

    /// The departments this node is associated with, if any.
    SDR_API
    const NdrTokenVec& GetDepartments() const { return _departments; }

    /// Gets the pages on which the node's properties reside (an aggregate of
    /// the unique `SdrShaderProperty::GetPage()` values for all of the node's
    /// properties). Nodes themselves do not reside on pages. In an example
    /// scenario, properties might be divided into two pages, 'Simple' and
    /// 'Advanced'.
    SDR_API
    const NdrTokenVec& GetPages() const { return _pages; };

    /// The list of primvars this node knows it requires / uses.
    /// For example, a shader node may require the 'normals' primvar to function
    /// correctly. Additional, user specified primvars may have been authored on
    /// the node. These can be queried via `GetAdditionalPrimvarProperties()`.
    /// Together, `GetPrimvars()` and `GetAdditionalPrimvarProperties()`,
    /// provide the complete list of primvar requirements for the node.
    SDR_API
    const NdrTokenVec& GetPrimvars() const { return _primvars; }

    /// The list of string input properties whose values provide the names of
    /// additional primvars consumed by this node. For example, this may return
    /// a token named `varname`. This indicates that the client should query the
    /// value of a (presumed to be string-valued) input attribute named varname
    /// from its scene description to determine the name of a primvar the 
    /// node will consume. See `GetPrimvars()` for additional information.
    SDR_API
    const NdrTokenVec& GetAdditionalPrimvarProperties() const {
        return _primvarNamingProperties;
    }

    /// Returns the implementation name of this node.  The name of the node
    /// is how to refer to the node in shader networks.  The label is how to
    /// present this node to users.  The implementation name is the name of
    /// the function (or something) this node represents in the
    /// implementation.  Any client using the implementation \b must call
    /// this method to get the correct name;  using \c getName() is not
    /// correct.
    SDR_API
    const std::string& GetImplementationName() const;

    /// @}


    /// \name Aggregate Information
    /// @{

    /// Gets the names of the properties on a certain page (one that was
    /// returned by `GetPages()`). To get properties that are not assigned to a
    /// page, an empty string can be used for \p pageName.
    SDR_API
    NdrTokenVec GetPropertyNamesForPage(const std::string& pageName) const;

    /// Gets all vstructs that are present in the shader.
    SDR_API
    NdrTokenVec GetAllVstructNames() const;

    /// @}


    /// \cond
    /// Hide from the API.

    // Performs a post-process on properties to determine information that can
    // only be determined after parsing or in aggregate. Clients SHOULD NOT
    // need to call this.
    void _PostProcessProperties();

    /// \endcond

protected:
    // Processed primvar metadata. `_primvars` contains the names of primvars
    // consumed by this node, whereas `_primvarNamingProperties` contains the
    // names of string input properties whose values provide the names of
    // additional primvars consumed by this node.
    NdrTokenVec _primvars;
    NdrTokenVec _primvarNamingProperties;

    // Tokenized metadata
    TfToken _label;
    TfToken _category;
    NdrTokenVec _departments;
    NdrTokenVec _pages;

    SdrPropertyMap _shaderInputs;
    SdrPropertyMap _shaderOutputs;

private:
    // Initializes `_primvars` and `_primvarNamingProperties`
    void _InitializePrimvars();

    // Determines which pages are present on the node's properties
    NdrTokenVec _ComputePages() const;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_USD_SDR_SHADER_NODE_H
