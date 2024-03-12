//
//  TwilioService.swift
//  OTPViaWhatsapp
//
//  Created by Kumar Anand on 06/03/24.
//

import Foundation

class TwilioService{
    
    let accountSID = "AC22581e961f786406656349ddb4c18ade"
    let authToken = "a7c64047b5cb1459974efdaf806cb1fb"
        
        func sendVerificationCode(to phoneNumber: String, completion: @escaping (Result<String, Error>) -> Void) {
            let url = URL(string: "https://verify.twilio.com/v2/Services/\(authToken)/Verifications")!
            
            var request = URLRequest(url: url)
            request.httpMethod = "POST"
            
            let body = "To=\(phoneNumber)&From=YOUR_TWILIO_PHONE_NUMBER&Body=Your%20verification%20code%20is%3A%20\(generateOTP())"
            request.httpBody = body.data(using: .utf8)
            
            let credentials = "\(accountSID):\(authToken)"
            let base64Credentials = Data(credentials.utf8).base64EncodedString()
            request.setValue("Basic \(base64Credentials)", forHTTPHeaderField: "Authorization")
            
            URLSession.shared.dataTask(with: request) { data, response, error in
                guard let data = data, let httpResponse = response as? HTTPURLResponse else {
                    completion(.failure(error ?? NSError(domain: "com.twilio.error", code: -1, userInfo: nil)))
                    return
                }
                
                if (200..<300).contains(httpResponse.statusCode) {
                    completion(.success("Verification code sent successfully"))
                } else {
                    completion(.failure(NSError(domain: "com.twilio.error", code: httpResponse.statusCode, userInfo: nil)))
                }
            }.resume()
        }
        
        func generateOTP() -> String {
            
            return "123456"
        }
    
    
    
    
    
    
}
