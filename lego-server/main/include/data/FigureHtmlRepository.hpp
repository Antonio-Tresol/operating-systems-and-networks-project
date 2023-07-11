// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>
#include <filesystem>
#include <vector>

/**
 * @brief Repository of Figure HTML.
 */
class FigureHtmlRepository {
public:

    /**
     * @brief Constructor. Searches for resource directory with HTML files.
     */
    FigureHtmlRepository();

    /**
     * @brief Finds and returns a given HTML string by figure name.
     * @param name Figure name to search for.
     * @return HTML string for given figure.
     */
    std::string findByName(const std::string &name) const;

    std::vector<std::string> getAvailableFigures() const;

private:
    static constexpr char RES[]{"res"};

    /**
     * @brief Locates the resource folder.
     * @return Resource folder path.
     */
    std::filesystem::path getResourcePath() const;

    std::vector<std::string> findAllHtmlFiles();

    std::vector<std::string> availableFigures{};
};
