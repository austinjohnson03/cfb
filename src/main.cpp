#include <cpr/cpr.h>

#include <CLI/CLI.hpp>
#include <cstdlib>
#include <iostream>

#define BASE_URL "https://api.collegefootballdata.com"

int main(int argc, char **argv) {
  CLI::App app{"cfb"};

  std::string endpoint;
  std::string year;
  std::string team;
  std::string week;

  app.add_option("-e,--endpoint", endpoint, "Endpoint being hit for");
  auto *year_opt = app.add_option("-y,--year", year, "Season year");
  auto *team_opt = app.add_option("-t,--team", team, "Team name");
  auto *week_opt = app.add_option("-w,--week", week, "Season week");

  CLI11_PARSE(app, argc, argv);

  if (endpoint.empty() || endpoint[0] != '/') {
    endpoint.insert(0, 1, '/');
  }

  const char *api_key = std::getenv("CFBD_API_KEY");

  if (!api_key) {
    std::cerr << "Error: CFBD_API_KEY environment variable not set.\n";
    return 1;
  }

  cpr::Parameters params;
  if (year_opt->count() > 0) params.Add({"year", year});
  if (team_opt->count() > 0) params.Add({"team", team});
  if (week_opt->count() > 0) params.Add({"week", week});

  auto response =
      cpr::Get(cpr::Url{BASE_URL + endpoint}, params,
               cpr::Header{{"Authorization", std::string("Bearer ") + api_key},
                           {"accept", "application/json"}});

  if (response.status_code != 200) {
    std::cerr << "Request failed (" << response.status_code
              << "): " << response.text << "\n";
    return 1;
  }

  std::cout << response.text << "\n";
  return 0;
}
