#include "StaticPage.h"
bool StaticPage::CheckRoute(Header thisHeader)
{
    if (thisHeader.Page == URI)
    {
        return true;
    }
    return false;
}
HTMLResponse StaticPage::Response(Header thisHeader)
{
    HTMLResponse response(fileContents, thisHeader.WebSession);
    std::vector<std::string> extensions;
    boost::split(extensions, URI, boost::is_any_of("."));
    if (extensions.size() > 1)
    {
        std::string extension = extensions.back();
        if (extension == "aac")
        {
            response.setContentType("audio/aac");
        }
        else if (extension == "abw")
        {
            response.setContentType("application/x-abiword");
        }
        else if (extension == "arc")
        {
            response.setContentType("application/x-freearc");
        }
        else if (extension == "avif")
        {
            response.setContentType("image/avif");
        }
        else if (extension == "avi")
        {
            response.setContentType("video/x-msvideo");
        }
        else if (extension == "azw")
        {
            response.setContentType("application/vnd.amazon.ebook");
        }
        else if (extension == "bin")
        {
            response.setContentType("application/octet-stream");
        }
        else if (extension == "bmp")
        {
            response.setContentType("image/bmp");
        }
        else if (extension == "bz")
        {
            response.setContentType("application/x-bzip");
        }
        else if (extension == "bz2")
        {
            response.setContentType("application/x-bzip2");
        }
        else if (extension == "cda")
        {
            response.setContentType("application/x-cdf");
        }
        else if (extension == "csh")
        {
            response.setContentType("application/x-csh");
        }
        else if (extension == "css")
        {
            response.setContentType("text/css");
        }
        else if (extension == "csv")
        {
            response.setContentType("text/csv");
        }
        else if (extension == "doc")
        {
            response.setContentType("application/msword");
        }
        else if (extension == "docx")
        {
            response.setContentType("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
        }
        else if (extension == "eot")
        {
            response.setContentType("application/vnd.ms-fontobject");
        }
        else if (extension == "epub")
        {
            response.setContentType("application/epub+zip");
        }
        else if (extension == "gz")
        {
            response.setContentType("application/gzip");
        }
        else if (extension == "gif")
        {
            response.setContentType("image/gif");
        }
        else if (extension == "ico")
        {
            response.setContentType("image/vnd.microsoft.icon");
        }
        else if (extension == "ics")
        {
            response.setContentType("text/calendar");
        }
        else if (extension == "jar")
        {
            response.setContentType("application/java-archive");
        }
        else if (extension == "jpeg" || extension == "jpg")
        {
            response.setContentType("image/jpeg");
        }
        else if (extension == "js")
        {
            response.setContentType("text/javascript");
        }
        else if (extension == "json")
        {
            response.setContentType("application/json");
        }
        else if (extension == "jsonld")
        {
            response.setContentType("application/ld+json");
        }
        else if (extension == "mid" || extension == "midi")
        {
            response.setContentType("audio/midi");
        }
        else if (extension == "mjs")
        {
            response.setContentType("text/javascript");
        }
        else if (extension == "mp3")
        {
            response.setContentType("audio/mpeg");
        }
        else if (extension == "mp4")
        {
            response.setContentType("video/mp4");
        }
        else if (extension == "mpeg")
        {
            response.setContentType("video/mpeg");
        }
        else if (extension == "mpkg")
        {
            response.setContentType("application/vnd.apple.installer+xml");
        }
        else if (extension == "odp")
        {
            response.setContentType("application/vnd.oasis.opendocument.presentation");
        }
        else if (extension == "ods")
        {
            response.setContentType("application/vnd.oasis.opendocument.spreadsheet");
        }
        else if (extension == "odt")
        {
            response.setContentType("application/vnd.oasis.opendocument.text");
        }
        else if (extension == "oga")
        {
            response.setContentType("audio/ogg");
        }
        else if (extension == "ogv")
        {
            response.setContentType("video/ogg");
        }
        else if (extension == "ogx")
        {
            response.setContentType("application/ogg");
        }
        else if (extension == "opus")
        {
            response.setContentType("audio/opus");
        }
        else if (extension == "otf")
        {
            response.setContentType("font/otf");
        }
        else if (extension == "png")
        {
            response.setContentType("image/png");
        }
        else if (extension == "pdf")
        {
            response.setContentType("application/pdf");
        }
        else if (extension == "php")
        {
            response.setContentType("application/x-httpd-php");
        }
        else if (extension == "ppt")
        {
            response.setContentType("application/vnd.ms-powerpoint");
        }
        else if (extension == "pptx")
        {
            response.setContentType("application/vnd.openxmlformats-officedocument.presentationm1.presentation");
        }
        else if (extension == "rar")
        {
            response.setContentType("application/vnd.rar");
        }
        else if (extension == "rtf")
        {
            response.setContentType("application/rtf");
        }
        else if (extension == "sh")
        {
            response.setContentType("application/x-sh");
        }
        else if (extension == "svg")
        {
            response.setContentType("image/svg+xml");
        }
        else if (extension == "tar")
        {
            response.setContentType("application/x-tar");
        }
        else if (extension == "tif" || extension == "tiff")
        {
            response.setContentType("image/tiff");
        }
        else if (extension == "ts")
        {
            response.setContentType("video/mp2t");
        }
        else if (extension == "ttf")
        {
            response.setContentType("font/ttf");
        }
        else if (extension == "txt")
        {
            response.setContentType("text/plain");
        }
        else if (extension == "vsd")
        {
            response.setContentType("application/vnd.visio");
        }
        else if (extension == "wav")
        {
            response.setContentType("audio/wav");
        }
        else if (extension == "weba")
        {
            response.setContentType("audio/webm");
        }
        else if (extension == "webm")
        {
            response.setContentType("video/webm");
        }
        else if (extension == "webp")
        {
            response.setContentType("image/webp");
        }
        else if (extension == "woff")
        {
            response.setContentType("font/woff");
        }
        else if (extension == "woff2")
        {
            response.setContentType("font/woff2");
        }
        else if (extension == "xhtml")
        {
            response.setContentType("application/xhtml+xml");
        }
        else if (extension == "xls")
        {
            response.setContentType("application/vnd.ms-excel");
        }
        else if (extension == "xlsx")
        {
            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        }
        else if (extension == "xml")
        {
            response.setContentType("application/xml");
        }
        else if (extension == "xul")
        {
            response.setContentType("application/vnd.mozilla.xul+xml");
        }
        else if (extension == "zip")
        {
            response.setContentType("application/zip");
        }
        else if (extension == "3gp")
        {
            response.setContentType("video/3gpp");
        }
        else if (extension == "3g2")
        {
            response.setContentType("video/3gpp2");
        }
        else if (extension == "7z")
        {
            response.setContentType("application/x-7z-compressed");
        }
    }
    return response;
}
StaticPage::StaticPage(std::string path)
{
    std::string CurrentFolder = Utilities::GetCurrentFolder() + "static";

    std::vector<std::string> stringParts;
    boost::split(stringParts, path.substr(CurrentFolder.length() + 1), boost::is_any_of("\\"));
    URI = "";
    for (size_t i = 0; i < stringParts.size(); i++)
    {
        URI += "/" + stringParts[i];
    }
    fileContents = Utilities::GetFileContents(path);
}