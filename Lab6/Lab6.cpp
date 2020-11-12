#include <httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <set>

const char url[] = "api.openweathermap.org";
const char get_url[] = "/data/2.5/forecast?q=Simferopol&appid=814ab893bb16e47e5c33b70202f2dd7d&units=metric";

// Заменяет определённую подстроку в шаблоне на значения из массива по очереди
void fillTemplate(std::string* t, const std::string& substr, const std::vector<std::string>& values)
{
    size_t index = 0;
    int values_ind = 0;
    while (true) {
        // Находим подстроку
        index = t->find(substr, index);
        if (index == std::string::npos) break;

        // Делаем замену
        t->erase(index, substr.size());
        t->insert(index, values[values_ind]);

        // На всякий случай, "перематываем" индекс вперёд, чтобы подстрока не заменилась на себя (в случае перекрывания)
        index += values[values_ind].size();

        values_ind++;
        if (values_ind >= values.size()) break;
    }
}

struct Data
{
    std::vector<std::string> dates, temps, icons;
    std::string city;
};

std::string extractIcon(const nlohmann::json& json)
{
    auto weather = json["weather"];
    for (auto& el : weather.items())
    {
        return el.value()["icon"];
    }
}

std::string floatToString(float f)
{
    std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << f;
    return ss.str();
}

Data parseData(const nlohmann::json& json)
{
    std::vector<std::string> dates, temps, icons;
    std::set<std::string> alreadyCheckedDate;

    auto city = json["city"]["name"].get<std::string>();

    auto list = json["list"];
    for (auto& el : list.items()) {
        std::string date = el.value()["dt_txt"];
        date = date.substr(0, date.find(' '));

        if (alreadyCheckedDate.find(date) == alreadyCheckedDate.end())
        {
            dates.push_back(date);

            auto temp = el.value()["main"]["temp"].get<float>();

            icons.push_back(extractIcon(el.value()));
            temps.push_back(floatToString(temp));

            alreadyCheckedDate.insert(date);
        }
    }

    return { dates, temps, icons, city };
}

// В этой функции формируем ответ сервера на запрос
void gen_response(const httplib::Request& req, httplib::Response& res) {
    httplib::Client cli(url, 80);

    auto weather_res = cli.Get(get_url);
    if (weather_res && weather_res->status == 200) {
        auto json = nlohmann::json::parse(weather_res->body);

        // Читаем весь файл
        std::ifstream ifs("Template.html");

        std::string Template, buffer;
        while (std::getline(ifs, buffer))
        {
            Template += buffer + '\n';
        }

        Data d = parseData(json);

        fillTemplate(&Template, "{city.name}", { d.city });

        fillTemplate(&Template, "{list.dt}", d.dates);
        fillTemplate(&Template, "{list.weather.icon}", d.icons);
        fillTemplate(&Template, "{list.main.temp}", d.temps);

        res.set_content(Template, "text/html");
    }
    else
        res.set_content("Failed to open api.openweather.org", "text/plain");
}

int main(void)
{
    httplib::Server svr;           // Создаём сервер
    svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
    svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 3000
}