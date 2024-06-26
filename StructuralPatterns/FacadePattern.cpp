//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Facade Pattern
// This pattern Provides a simplified interface to a complex system of classes, making the subsystem easier to use.

// In this example, Facade Pattern is implemented through the `MultimediaFacade` class, which provides a simplified
// interface for the client to interact with complex subsystems such as `AudioPlayer`, `VideoPlayer`, and `DisplayController`.

#include <iostream>
#include <memory>

// Subsystem 1
class AudioPlayer {
public:
    void playAudio(const std::string& fileName) const {
        std::cout << "Playing audio file: " << fileName << std::endl;
    }
};

// Subsystem 2
class VideoPlayer {
public:
    void playVideo(const std::string& fileName) const {
        std::cout << "Playing video file: " << fileName << std::endl;
    }
};

// Subsystem 3
class DisplayController {
public:
    void displayOutput() const {
        std::cout << "Displaying output" << std::endl;
    }
};

// Enum for media types
enum class MediaType {
    Audio,
    Video,
    Unsupported
};

// Facade
class MultimediaFacade {
private:
    AudioPlayer audioPlayer;
    VideoPlayer videoPlayer;
    DisplayController displayController;

public:
    void playMedia(const std::string& fileName, MediaType mediaType) const {
        switch (mediaType) {
            case MediaType::Audio:
                audioPlayer.playAudio(fileName);
                break;
            case MediaType::Video:
                videoPlayer.playVideo(fileName);
                break;
            default:
            std::cout << "Unsupported media type" << std::endl;
        }
        displayController.displayOutput();
    }
};

int main() {
    std::unique_ptr<MultimediaFacade> multimediaFacade = std::make_unique<MultimediaFacade>();
        multimediaFacade->playMedia("song.mp3", MediaType::Audio);
        multimediaFacade->playMedia("movie.mp4", MediaType::Video);
        multimediaFacade->playMedia("image.jpg", MediaType::Unsupported); // Will throw an exception
    return 0;
}
