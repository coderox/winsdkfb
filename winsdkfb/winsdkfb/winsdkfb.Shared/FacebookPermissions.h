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

#include <winrt/Windows.Foundation.Collections.h>

namespace winsdkfb
{
    /*!\brief Simple class to contain a set of permissions for FB.
    */
    struct FBPermissions : winrt::implements<FBPermissions, winrt::Windows::Foundation::IStringable>
	{
		public:
            //! Construct an instance with a given set of permissions
            FBPermissions(
                winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> const& Permissions
                );

            //! The list of permissions
			winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> Values();

            //! Handy override that provides a string version of permissions in
            // the format suitable for concatenating into a FB request URL.
			virtual winrt::hstring ToString();

            /**
             * Constructs an instance of FBPermissions
             * @param Permissions A comma seperated list of permissions
             */
            static FBPermissions FromString(
                winrt::hstring const& Permissions
                );

            /**
             * Returns the set difference of two FBPermissions' permissions
             * @param Minuend FBPermissions to subtract from
             * @param Subtrahend FBPermissions to 'remove' from Minuend
             * @return a new FBPermissions object that contains the set of
             * permissions that exist in Minuend and not in Subtrahend
             */
            static FBPermissions Difference(FBPermissions const& Minuend, FBPermissions const& Subtrahend);

		private:
            static winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> ParsePermissionsFromString(
                winrt::hstring const& Permissions
                );

			winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> _values;
	};
}
