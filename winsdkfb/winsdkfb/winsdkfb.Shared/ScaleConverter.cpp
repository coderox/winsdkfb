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

#include "pch.h"
#include "ScaleConverter.h"
#include <string>

using namespace winsdkfb;
using namespace std;
using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml::Data;
using namespace winrt::Windows::UI::Xaml::Interop;

winrt::Windows::Foundation::IInspectable ScaleConverter::Convert(
	winrt::Windows::Foundation::IInspectable const& value,
	winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
	winrt::Windows::Foundation::IInspectable const & parameter,
	winrt::hstring const& language
)
{
    if (targetType.Name != L"double")
    {
		throw hresult_invalid_argument();
    }

    double numValue = winrt::unbox_value<double>(value);

    hstring paramString = parameter.as<IStringable>().ToString();

    double numParam = stod(wstring(paramString.data()));

    return box_value(numValue * numParam);
}
