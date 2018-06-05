//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#pragma once

#include <winrt/Windows.Foundation.Metadata.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace winsdkfb
{
    struct ScaleConverter : winrt::implements<ScaleConverter, winrt::Windows::UI::Xaml::Data::IValueConverter>
    {
        winrt::Windows::Foundation::IInspectable Convert(
			winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
			winrt::Windows::Foundation::IInspectable const & parameter,
            winrt::hstring const& language
            );

        winrt::Windows::Foundation::IInspectable ConvertBack(
			winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::UI::Xaml::Interop::TypeName targetType,
			winrt::Windows::Foundation::IInspectable const& parameter,
			winrt::hstring const& language
            )
        {
            throw winrt::hresult_not_implemented();
        }
    };
}

