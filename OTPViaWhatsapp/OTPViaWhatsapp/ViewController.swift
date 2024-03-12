//
//  ViewController.swift
//  OTPViaWhatsapp
//
//  Created by Kumar Anand on 06/03/24.
//

import UIKit
import TwilioVerifySDK

class ViewController: UIViewController {

    @IBOutlet weak var phoneNumberTxt: UITextField!
    
    @IBOutlet weak var sendOTPBtn: UIButton!
    let twilioService = TwilioService()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        uiDesign()
    }
    
    func uiDesign(){
        sendOTPBtn.layer.cornerRadius = 5
        
    }
    
    
    @IBAction func sendBtnOtpAction(_ sender: UIButton) {
        let phoneNumber = phoneNumberTxt.text ?? ""
        let otp = "1234"
        sendOTP(phoneNumber: phoneNumber, otp: otp)
         
    }
    
    
    func sendOTP(phoneNumber: String, otp: String) {
        let accountSID = "AC22581e961f786406656349ddb4c18ade"
        let authToken = "a7c64047b5cb1459974efdaf806cb1fb"
        let twilioNumber = "9752202369"
        
        let url = URL(string: "https://api.twilio.com/2010-04-01/Accounts/\(accountSID)/Messages.json")!
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        
        let body = "From=whatsapp:\(twilioNumber)&Body=Your+OTP+is+\(otp)&To=whatsapp:\(phoneNumber)"
        request.httpBody = body.data(using: .utf8)
        
        request.setValue("Basic \(base64EncodedCredentials())", forHTTPHeaderField: "Authorization")
        request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")
        
        let task = URLSession.shared.dataTask(with: request) { data, response, error in
            if let error = error {
                print("Error sending OTP: \(error)")
            } else if let data = data {
                print("OTP sent successfully!")
                
            }
        }
        task.resume()
    }

    func base64EncodedCredentials() -> String {
        let accountSID = "AC22581e961f786406656349ddb4c18ade"
        let authToken = "a7c64047b5cb1459974efdaf806cb1fb"
        let credentials = "\(accountSID):\(authToken)"
        let data = credentials.data(using: .utf8)!
        return data.base64EncodedString()
    }
    

}

