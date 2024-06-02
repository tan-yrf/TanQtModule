#include "commonfileprocessor.h"

#include <QDir>
#include <QStandardPaths>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

CommonFileProcessor::CommonFileProcessor(QObject* parent): QObject(parent)
{}

// 在指定位置下创建文件夹
bool CommonFileProcessor::CreateFolderInTargetFolder(const QString target_folder, const QString folder_name)
{
    QString folder_path = target_folder + QDir::separator() + folder_name;
    QDir dir(folder_path);
    if(!dir.exists())
    {
        if(!dir.mkpath("."))
        {
            // 创建失败
            return false;
        }
    }
    return true;
}

// 在用户目录下创建配置文件夹
bool CommonFileProcessor::CreateConfigFolderInUser(const QString config_folder_name)
{
    QString user_home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    if(CreateFolderInTargetFolder(user_home_path, config_folder_name))
    {
        // 创建成功，记录配置文件夹路径
        m_config_folder_path = user_home_path + QDir::separator() + config_folder_name;
        return true;
    }
    return false;
}

// 在指定位置创建文件
bool CommonFileProcessor::CreateFileInTargetPath(const QString file_path)
{
    QFile file(file_path);

    // 尝试打开文件以确保可写性
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return false;
    }
    file.close();
    return true;
}

bool CommonFileProcessor::CreateFileInTargetFolder(const QString target_folder, const QString file_name)
{
    // 文件夹不存在，且创建失败
    QDir dir(target_folder);
    if(!dir.exists() && !dir.mkpath("."))
    {
        return false;
    }
    QString file_path = QDir::cleanPath(target_folder + QDir::separator() + file_name);

    return CreateFileInTargetPath(file_path);
}

// 获取配置文件夹路径
QString CommonFileProcessor::GetConfigFolderPath() const
{
    return m_config_folder_path;
}

// 将json对象写入指定位置，如果文件不存在就创建一个json文件
bool CommonFileProcessor::WriteJsonToFile(const QString file_path, const QJsonDocument &json_doc)
{
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    qint64 bytes_written = file.write(json_doc.toJson());
    if (bytes_written == 0) // 检查写入是否成功
    {
        qWarning() << "Failed to write to file:" << file.errorString();
        file.close();
        return false;
    }

    file.close(); // 关闭文件
    return true;
}

// 读取指定json文件
QJsonDocument CommonFileProcessor::ReadJsonFromFile(const QString file_path) const
{
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        return QJsonDocument();
    }

    QByteArray file_data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument json_doc = QJsonDocument::fromJson(file_data, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << u8"json解析失败:" << error.errorString();
        return QJsonDocument();
    }

    return json_doc;
}
