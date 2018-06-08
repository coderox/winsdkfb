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
#include "FacebookError.h"

using namespace Platform;
using namespace winsdkfb;
using namespace winrt;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

FBError::FBError(
    ) :
    _code(0),
    _subcode(0)
{
    ;
}

hstring FBError::Message()
{
    return _message;
}

hstring FBError::Type()
{
    return _type;
}

int FBError::Code()
{
    return _code;
}

int FBError::Subcode()
{
    return _subcode;
}

hstring FBError::ErrorUserTitle()
{
    return _errorUserTitle;
}

hstring FBError::ErrorUserMessage()
{
    return _errorUserMessage;
}


FBError FBError::FromUri(
    Uri const& ResponseUri
    )
{
	FBError err;
    bool foundCode = false;
    bool foundDescription = false;
    bool foundMessage = false;
    bool foundReason = false;
    int code = 0;
	hstring reason;
    hstring description;
    hstring message;
    hstring query = ResponseUri.Query();

    if (!query.empty())
    {
        auto decoder = make<WwwFormUrlDecoder>(ResponseUri.Query());

        for (unsigned int i = 0; i < decoder->Size; i++)
        {
            IWwwFormUrlDecoderEntry entry = decoder->GetAt(i);
            if (entry.Name() == L"error_code")
            {
                foundCode = true;
                code = _wtoi(entry.Value().data());
            }
            else if (entry.Name() == L"error_description")
            {
                foundDescription = true;
                description = entry.Value();
            }
            else if (entry.Name() == L"error_message")
            {
                foundMessage = true;
                message = entry.Value();
            }
            else if (entry.Name() == L"error_reason")
            {
                foundReason = true;
                reason = entry.Value();
            }
        }

        if (foundCode || foundDescription || foundMessage || foundReason)
        {
            err._code = code;
            err._type = reason;
            if (foundDescription)
            {
                err._message = description;
            }
            else
            {
                err._message = message;
            }
        }
    }

    return err;
}

FBError FBError::FromJson(
	hstring const& JsonText
)
{
	FBError result;
	int found = 0;
	JsonValue val{ nullptr };

	if (JsonValue::TryParse(JsonText, val))
	{
		if (val.ValueType() == JsonValueType::Object)
		{
			JsonObject obj = val.GetObject();
			for (auto&& current : obj)
			{
				winrt::hstring key = current.Key();
				
				if (key == L"message")
				{
					found++;
					result._message = current.Value().GetString();
				}
				else if (key == L"type")
				{
					found++;
					result._type = current.Value().GetString();
				}
				else if (key == L"code")
				{
					found++;
					result._code = static_cast<int>(current.Value().GetNumber());
				}
				else if (key == L"error_subcode")
				{
					found++;
					result._subcode = static_cast<int>(current.Value().GetNumber());
				}
				else if (key == L"error_user_title")
				{
					found++;
					result._errorUserTitle = current.Value().GetString();
				}
				else if (key == L"error_user_msg")
				{
					found++;
					result._errorUserMessage = current.Value().GetString();
				}
			}
		}
	}
	return result;
}

FBError::FBError(
    int Code,
    hstring const& Type,
    hstring const& Message
    ) :
    _code(Code),
    _message(Message),
    _subcode(0),
    _type(Type)
{
    ;
}
