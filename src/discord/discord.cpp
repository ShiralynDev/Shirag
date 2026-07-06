#include "discord.hpp"

#define DISCORDPP_IMPLEMENTATION
#include <discordpp.h>

#include <iostream>

void Shirag::Discord::init(uint64_t AppID) {
    client->AddLogCallback([](auto message, auto severity) {
        std::cout << "[" << EnumToString(severity) << "] " << message << std::endl;
    },
                           discordpp::LoggingSeverity::Info);

    client->SetStatusChangedCallback([this](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
        std::cout << "Status changed: " << discordpp::Client::StatusToString(status) << std::endl;

        if (status == discordpp::Client::Status::Ready) {
            std::cout << "Client is ready! You can now call SDK functions.\n";
        } else if (error != discordpp::Client::Error::None) {
            std::cerr << "Connection Error: " << discordpp::Client::ErrorToString(error) << " - Details: " << errorDetail << std::endl;
        }
    });

    client->SetApplicationId(AppID);

    activity.SetType(discordpp::ActivityTypes::Playing);

    client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
        if (result.Successful()) {
            std::cout << "Rich Presence updated successfully!\n";
        } else {
            std::cerr << "Rich Presence update failed";
        }
    });
}

void Shirag::Discord::runCallbacks() {
    discordpp::RunCallbacks();
}

void Shirag::Discord::setActivityState(std::string stateText) {
    activity.SetState(stateText);
}

void Shirag::Discord::setActivityDetails(std::string detailsText) {
    activity.SetDetails(detailsText);
}

void Shirag::Discord::updateActivity() {
    client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {});
}