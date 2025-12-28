add_library(
  mediaelch_scraper_movie_theporndb OBJECT
  ThePornDbApi.cpp
  ThePornDbMovie.cpp
  ThePornDbMovieConfiguration.cpp
  ThePornDbMovieScrapeJob.cpp
  ThePornDbMovieSearchJob.cpp
)

target_link_libraries(
  mediaelch_scraper_movie_theporndb
  PRIVATE Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Widgets
)

mediaelch_post_target_defaults(mediaelch_scraper_movie_theporndb)
