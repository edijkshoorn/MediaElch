#include "scrapers/image/LocalImages.h"

#include "data/movie/Movie.h"
#include "data/tv_show/SeasonNumber.h"
#include "log/Log.h"
#include "media/Path.h"
#include "settings/DataFile.h"
#include "settings/Settings.h"

#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QSet>
#include <QUrl>

namespace mediaelch {
namespace scraper {

const QString LocalImages::ID = "images.local";

LocalImages::LocalImages(QObject* parent) : ImageProvider(parent)
{
    m_meta.identifier = ID;
    m_meta.name = QObject::tr("Local files");
    m_meta.description = QObject::tr("Use images that already exist next to the movie files.");
    m_meta.website = QUrl();
    m_meta.supportedImageTypes = {ImageType::MoviePoster,
        ImageType::MovieBackdrop,
        ImageType::MovieLogo,
        ImageType::MovieBanner,
        ImageType::MovieThumb,
        ImageType::MovieClearArt,
        ImageType::MovieCdArt};
    m_meta.defaultLocale = mediaelch::Locale::NoLocale;
}

const ImageProvider::ScraperMeta& LocalImages::meta() const
{
    return m_meta;
}

void LocalImages::movieImages(Movie* movie, TmdbId tmdbId, QSet<ImageType> types)
{
    Q_UNUSED(tmdbId)
    setCurrentMovie(movie);

    QMap<ImageType, QVector<Poster>> posters;
    for (const ImageType type : types) {
        posters.insert(type, gatherMovieImages(type));
    }

    emit sigMovieImagesLoaded(movie, posters);
}

void LocalImages::moviePosters(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MoviePoster);
}

void LocalImages::movieBackdrops(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieBackdrop);
}

void LocalImages::movieLogos(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieLogo);
}

void LocalImages::movieBanners(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieBanner);
}

void LocalImages::movieThumbs(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieThumb);
}

void LocalImages::movieClearArts(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieClearArt);
}

void LocalImages::movieCdArts(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
    emitImagesForMovieType(ImageType::MovieCdArt);
}

void LocalImages::concertImages(Concert* concert, TmdbId tmdbId, QSet<ImageType> types)
{
    Q_UNUSED(concert)
    Q_UNUSED(tmdbId)
    Q_UNUSED(types)
}

void LocalImages::concertPosters(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
}

void LocalImages::concertBackdrops(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
}

void LocalImages::concertLogos(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
}

void LocalImages::concertClearArts(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
}

void LocalImages::concertCdArts(TmdbId tmdbId)
{
    Q_UNUSED(tmdbId)
}

void LocalImages::tvShowImages(TvShow* show, TvDbId tvdbId, QSet<ImageType> types, const mediaelch::Locale& locale)
{
    Q_UNUSED(show)
    Q_UNUSED(tvdbId)
    Q_UNUSED(types)
    Q_UNUSED(locale)
}

void LocalImages::tvShowPosters(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowBackdrops(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowLogos(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowClearArts(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowCharacterArts(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowBanners(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::tvShowEpisodeThumb(TvDbId tvdbId, SeasonNumber season, EpisodeNumber episode, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(season)
    Q_UNUSED(episode)
    Q_UNUSED(locale)
}

void LocalImages::tvShowSeason(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(season)
    Q_UNUSED(locale)
}

void LocalImages::tvShowSeasonBanners(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(season)
    Q_UNUSED(locale)
}

void LocalImages::tvShowSeasonBackdrops(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(season)
    Q_UNUSED(locale)
}

void LocalImages::tvShowSeasonThumbs(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(season)
    Q_UNUSED(locale)
}

void LocalImages::tvShowThumbs(TvDbId tvdbId, const mediaelch::Locale& locale)
{
    Q_UNUSED(tvdbId)
    Q_UNUSED(locale)
}

void LocalImages::artistFanarts(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::artistLogos(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::artistThumbs(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::albumCdArts(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::albumThumbs(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::albumBooklets(MusicBrainzId mbId)
{
    Q_UNUSED(mbId)
}

void LocalImages::artistImages(Artist* artist, MusicBrainzId mbId, QSet<ImageType> types)
{
    Q_UNUSED(artist)
    Q_UNUSED(mbId)
    Q_UNUSED(types)
}

void LocalImages::albumImages(Album* album, MusicBrainzId mbId, QSet<ImageType> types)
{
    Q_UNUSED(album)
    Q_UNUSED(mbId)
    Q_UNUSED(types)
}

void LocalImages::setCurrentMovie(Movie* movie)
{
    m_currentMovie = movie;
}

void LocalImages::searchMovie(QString searchStr, int limit)
{
    Q_UNUSED(searchStr)
    Q_UNUSED(limit)

    QVector<ScraperSearchResult> results;
    if (m_currentMovie != nullptr) {
        ScraperSearchResult result;
        result.id = m_currentMovie->tmdbId().toString();
        result.name = m_currentMovie->title();
        result.released = m_currentMovie->released();
        results.append(result);
    }

    emit sigSearchDone(results, {});
}

void LocalImages::searchConcert(QString searchStr, int limit)
{
    Q_UNUSED(searchStr)
    Q_UNUSED(limit)
    emit sigSearchDone({}, {});
}

void LocalImages::searchTvShow(QString searchStr, mediaelch::Locale locale, int limit)
{
    Q_UNUSED(searchStr)
    Q_UNUSED(locale)
    Q_UNUSED(limit)
    emit sigSearchDone({}, {});
}

void LocalImages::searchArtist(QString searchStr, int limit)
{
    Q_UNUSED(searchStr)
    Q_UNUSED(limit)
    emit sigSearchDone({}, {});
}

void LocalImages::searchAlbum(QString artistName, QString searchStr, int limit)
{
    Q_UNUSED(artistName)
    Q_UNUSED(searchStr)
    Q_UNUSED(limit)
    emit sigSearchDone({}, {});
}

QVector<Poster> LocalImages::gatherMovieImages(ImageType type) const
{
    QVector<Poster> posters;
    if (m_currentMovie == nullptr || m_currentMovie->files().isEmpty()) {
        return posters;
    }

    const mediaelch::FileList& movieFiles = m_currentMovie->files();
    const mediaelch::FilePath& mainFile = movieFiles.first();
    const QDir directory = mainFile.dir().dir();

    QSet<QString> seenFiles;
    auto addPoster = [&posters, &seenFiles](const QString& path) {
        if (seenFiles.contains(path)) {
            return;
        }
        if (!QFileInfo::exists(path)) {
            return;
        }

        Poster poster;
        poster.id = path;
        poster.originalUrl = QUrl::fromLocalFile(path);
        poster.thumbUrl = poster.originalUrl;
        poster.hint = QFileInfo(path).fileName();
        posters.append(poster);
        seenFiles.insert(path);
    };

    const bool isStacked = movieFiles.count() > 1;
    const auto configuredNames = Settings::instance()->dataFiles(type);
    for (const DataFile& dataFile : configuredNames) {
        const QString candidate = directory.filePath(dataFile.saveFileName(mainFile.fileName(), SeasonNumber::NoSeason, isStacked));
        addPoster(candidate);
    }

    const QStringList filters{"*.jpg", "*.jpeg", "*.png", "*.bmp", "*.webp", "*.tbn"};
    const auto localFiles = directory.entryInfoList(filters, QDir::Files | QDir::Readable, QDir::Name);
    for (const QFileInfo& info : localFiles) {
        addPoster(info.absoluteFilePath());
    }

    return posters;
}

void LocalImages::emitImagesForMovieType(ImageType type)
{
    emit sigImagesLoaded(gatherMovieImages(type), {});
}

} // namespace scraper
} // namespace mediaelch

