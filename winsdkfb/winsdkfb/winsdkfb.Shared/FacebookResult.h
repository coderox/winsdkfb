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

#include <winrt/Windows.Foundation.h>
#include "FacebookError.h"
#include "FacebookAccessTokenData.h"

namespace winsdkfb
{
    /*!\brief Container class holding the result of a graph API call - either a
     * JSON object of some type, or an error, depending on the value of the
     * Succeeded property. Note that the instantiation of Object and ErrorInfo
     * are exclusive to each other, only one can be instantiated at a time.
     */
    class FBResult
    {
        public:

            /**
             * Contructor for FBResult.
             * @param Object Additional information that FBResult can carry back
             * to the caller. If Object can be cast to FBError the FBResult will
             * be considered unsuccessful, otherwise it will be considered
             * successful.
             */
            FBResult(
                winrt::Windows::Foundation::IInspectable const& Object
                );

            /**
             * Indicates that the operation associated with the FBResult was
             * successful or not. Use to determine whether the Object or ErrorInfo
             * field should be accessed for more information.
             */
            bool Succeeded();            

            /**
             * A context dependent object used to send additional data with the
             * FBResult. Object will need to be cast to different types depending
             * on the operation that generated it in order to be used.
             */
            winrt::Windows::Foundation::IInspectable Object();

            /**
             * Error information sent from the operation that created the
             * FBResult.
             */
            winsdkfb::FBError ErrorInfo();            

        private:
            ~FBResult(
                );

			winrt::Windows::Foundation::IInspectable _Object{ nullptr };
			winsdkfb::FBError _Error{ nullptr };
    };
}
