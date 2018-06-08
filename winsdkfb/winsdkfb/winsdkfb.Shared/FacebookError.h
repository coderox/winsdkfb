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

namespace winsdkfb
{
    /*!
     * \brief error codes.
     */
    enum ErrorCode : int
    {
        ErrorCodeOauthException = 190,
        ErrorCodeWebAccountProviderNotFound = 5000,
        ErrorCodeWebTokenRequestStatus = 5001,
        ErrorCodeWebAccountProviderNotSupported = 5002,
    };

    /*!
     * \brief error subcodes.
     */
    enum ErrorSubcode : int
    {
        ErrorSubcodeAppNotAuthorized   = 458,
        ErrorSubcodeSessionInvalidated = 466
    };

    /*!
     * \brief class wrapper for FB error responses. For the time being, this is
     * a very bare shell around the error response URL from Facebook, and not a
     * full-blown error class such as exists in the Facebook SDK for iOS.
     */
    struct FBError : winrt::implements<FBError, winrt::Windows::Foundation::IInspectable>
    {
        public:
            /**
             * Tries to instantiate an FBError object based off of a response
             * URI from Facebook.
             * @param ResponseUri Response URI to extract error information from.
             * @return FBError object encapsulating error data from the URI.
             * Will return nullptr if the URI doesn't contain an error.
             */
            static FBError FromUri(
                winrt::Windows::Foundation::Uri const& ResponseUri
                );

            /**
             * Tries to instantiate an FBError object from a JSON formatted
             * string.
             * @param JsonText JSON string to extract error information from.
             * @return FBError object encapsulating the JSON string error data.
             * Will return nullptr if JsonText is not properly formatted JSON
             * or if it doesn't contain an error.
             */
            static FBError FromJson(
                winrt::hstring const& JsonText
                );

            FBError(
                int Code,
                winrt::hstring const& Type,
                winrt::hstring const& Message
                );

            //! Error message string
            winrt::hstring Message();

            //! Error type string
            winrt::hstring Type();

            //! Error code
            int Code();

            //! Error subcode
            int Subcode();

            //! Error user title
            winrt::hstring ErrorUserTitle();

            //! Error user message
            winrt::hstring ErrorUserMessage();

        private:
            FBError(
                );

            winrt::hstring	_message;
            winrt::hstring	_type;
            int				_code;
            int				_subcode;
            winrt::hstring  _errorUserTitle;
            winrt::hstring	_errorUserMessage;
    };
}
