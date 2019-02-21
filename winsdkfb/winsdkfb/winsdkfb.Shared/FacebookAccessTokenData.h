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

#include "FacebookPermissions.h"

namespace winsdkfb
{
    /**
     * @brief Represents an access token used for Facebook login, with
     * associated data.
     */
    public ref class FBAccessTokenData sealed
    {
        public:
            /**
             * Attempts to create a FBAccessTokenData object from a URI.
             * @param Response The URI to construct a FBAccessTokenData object from
             * @return An FBAccessTokenData representation of the URI's data, or
             * nullptr if the URI is invalid
             */
            static FBAccessTokenData^ FromUri(
                Windows::Foundation::Uri^ Response
                );

            FBAccessTokenData(
                Platform::String^ AccessToken,
                Windows::Foundation::DateTime Expiration,
				Windows::Foundation::DateTime DataAccessExpiration
                );

            /**
             * Access token provided by Facebook on successful login.
             */
            property Platform::String^ AccessToken
            {
                Platform::String^ get();
            }

            /**
             * Expiration date of the access token.
             */
            property Windows::Foundation::DateTime ExpirationDate
            {
                Windows::Foundation::DateTime get();
            }

			/**
			 * Expiration date of the data access permissions.
			 */
			property Windows::Foundation::DateTime DataAccessExpirationDate
			{
				Windows::Foundation::DateTime get();
			}

            /**
             * The permissions that were granted by the user.
             */
            property winsdkfb::FBPermissions^ GrantedPermissions
            {
                winsdkfb::FBPermissions^ get();
            }

            /**
             * The permissions that were declined by the user.
             */
            property winsdkfb::FBPermissions^ DeclinedPermissions
            {
                winsdkfb::FBPermissions^ get();
            }

            /**
             * Compares the expiration time of the access token to the current time.
             * @return true if the access token is expired, false otherwise.
             */
            bool IsExpired(
                );

			/**
			 * Compares the data access expiration time of the access token to the current time.
			 * @return true if the data access permissions is expired, false otherwise.
			 */
			bool IsDataAccessExpired(
			);

			/**
			 * Since older tokens didn't have Data Access Expiration, we need to expose that
			 * @return true if the token has a data access expiration date, false otherwise.
			 */
			bool HasDataAccessExpirationDate(
			) {
				return _hasDataAccessExpirationDate;
			}

            /**
             * Splits permissions into granted and declined groups then stores
             * these as GrantedPermissions and DeclinedPermissions,
             * respectively. Note that previous values for GrantedPermissions
             * and DeclinedPermissions will be overwritten.
             * @param perms Collection of permissions to divide.
             */
            void SetPermissions(
                Windows::Foundation::Collections::IVectorView<Object^>^ perms
                );

        private:
            FBAccessTokenData(
                Platform::String^ AccessToken,
                Platform::String^ Expiration,
				Platform::String^ DataAccessExpiration
                );

            /**
             * Converts expiration string to DateTime object that indicates when
             * the access token will expire. This value may be accessed via
             * ExpirationDate.
             * @param Expiration The date to convert.
             */
            void CalculateExpirationDateTime(
                Platform::String^ Expiration
                );

			/**
			 * Converts data access expiration string to DateTime object that indicates when
			 * the data access permissions will expire. This value may be accessed via
			 * DataAccessExpirationDate.
			 * @param DataAccessExpiration The date to convert.
			 */
			void CalculateDataAccessExpirationDateTime(
				Platform::String^ DataAccessExpiration
			);

            static Windows::Foundation::WwwFormUrlDecoder^
            ParametersFromResponse(
                Windows::Foundation::Uri^ Response
                );

#ifdef _DEBUG
            void DebugPrintExpirationTime(
                );
#endif

            Platform::String^ _accessToken;
            Windows::Foundation::DateTime _expirationDate;
			Windows::Foundation::DateTime _dataAccessExpirationDate;
            FBPermissions^ _grantedPermissions;
            FBPermissions^ _declinedPermissions;
			bool _hasDataAccessExpirationDate;
    };
}
