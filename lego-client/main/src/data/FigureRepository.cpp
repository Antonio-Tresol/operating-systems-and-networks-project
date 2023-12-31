// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/data/FigureRepository.hpp"

using std::string;

FigureRepository::FigureRepository(const std::string &host) : host(host) {}

Figure FigureRepository::findByName(const string& name) const {
    const string url{URL_TEMPLATE + name};
    const string html{httpsClient.get(host, url)};

    return Figure::fromHtml(html);
}
