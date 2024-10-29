#--Import BeautifulSoup:
import requests
from bs4 import BeautifulSoup

http_text = requests.get("https://weather.com/en-CA/weather/tenday/l/63f4de10a8c7b229661a9674a3d0915b9740827451d381e82b730ca1b96bbbf5").text
#print(http_text)

soup = BeautifulSoup(http_text, 'lxml') #initialize BeautifulSoup

#--Find weather data:
weather_data = soup.find_all('div', class_="DetailsSummary--DetailsSummary--1DqhO DetailsSummary--fadeOnOpen--KnNyF")
#print(len(weather_data))

final_data = ""

for day in weather_data:
    date = day.find('h3', class_="DetailsSummary--daypartName--kbngc").text #get date
    #print(date)
    #--Find Temps:
    temp_section = day.find('div', class_="DetailsSummary--temperature--1kVVp")
    span_tags = temp_section.find_all('span')
    max_temp = span_tags[0].text
    min_temp = span_tags[1].span.text
    #print(max_temp)
    #print(min_temp)
    #--Weather Conditions:
    weather_condition = day.find('div', class_="DetailsSummary--condition--2JmHb").span.text
    #print(weather_condition)
    #--Chance of Rain/Snow
    chance = day.find('div', class_="DetailsSummary--precip--1a98O").span.text
    #print(chance)
    #--Wind:
    wind_section = day.find('div', class_="DetailsSummary--wind--1tv7t DetailsSummary--extendedData--307Ax").span.text
    #print(wind_section)
    wind_separated = wind_section.split()
    #print(wind_separated)
    wind_direction = wind_separated[0]
    wind_speed = wind_separated[1]
    #print(wind_direction)
    #print(wind_speed)
    #--Final Data:
    final_data += date + ", " + max_temp+ ", " + min_temp+ ", " + weather_condition+ ", " + chance+ ", " + wind_direction+ ", " + wind_speed + "\n"
print(final_data)
with open('ELEC390_Lab2_Updated.txt', 'a') as f:
    print(final_data, file=f)
