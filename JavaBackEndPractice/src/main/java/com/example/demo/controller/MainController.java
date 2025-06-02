package com.example.demo.controller;

import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class MainController {

    @GetMapping("/")
    public String index(Model model, @AuthenticationPrincipal OAuth2User principal) {
        if (principal != null) {
            String name = principal.getAttribute("name");
            String login = principal.getAttribute("login");
            String avatarUrl = principal.getAttribute("avatar_url");

            model.addAttribute("name", name);
            model.addAttribute("login", login);
            model.addAttribute("avatarUrl", avatarUrl);
        }
        return "index";
    }
}
