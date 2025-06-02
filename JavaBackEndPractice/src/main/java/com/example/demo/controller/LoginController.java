package com.example.demo.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class LoginController {

    @GetMapping("/login")
    public String login() {
        return "login";  // 返回 login.html 模板
    }

    @GetMapping("/home")
    public String home() {
        return "home";   // 登录成功后跳转 home.html
    }
}
