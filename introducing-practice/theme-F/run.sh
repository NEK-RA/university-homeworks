#!/bin/bash
# API-ключ от OpenWeatherMap начинает работать не сразу, поэтому при использовании сразу после получения ключа OWM будет сыпать ошибки
clear
BOT_TOKEN="Токен из сообщества в VK" OWM_KEY="OpenWeatherMap API-ключ" python main.py
