/*
 * @brief 文件处理模块，实现文件相关的操作，尤其是json文件的读写等。
 * @note 如果需要使用到配置文件相关部分，最好先尝试创建配置文件夹。
*/
#ifndef COMMONFILEPROCESSOR_H
#define COMMONFILEPROCESSOR_H

#include "CommonFileProcessor_global.h"
#include <QObject>

class COMMONFILEPROCESSOR_EXPORT CommonFileProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CommonFileProcessor(QObject* parent = nullptr);

    /**
    * @brief CreateFolderInTargetFolder 在指定位置下创建文件夹
    * @param target_path 指定位置
    * @return true表示创建成功或者文件夹已经存在，false表示创建失败
    */
    bool CreateFolderInTargetFolder(const QString target_folder, const QString folder_name);

    /**
    * @brief  CreateConfigFolderInUser 在用户目录下创建配置文件夹
    * @param config_folder_name 配置文件夹名
    * @return true表示创建成功，false表示创建失败
    */
    bool CreateConfigFolderInUser(const QString config_folder_name);

    /**
    * @brief CreateFileInTargetPath 在指定位置创建文件
    * @param file_path 文件路径
    * @return true表示文件已存在或者创建成功，false表示创建失败
    */
    bool CreateFileInTargetPath(const QString file_path);

    /**
    * @brief CreateFileInTargetPath 在指定位置创建文件
    * @param file_path 文件路径
    * @return true表示文件已存在或者创建成功，false表示创建失败
    */
    bool CreateFileInTargetFolder(const QString target_folder, const QString file_name);

    /**
    * @brief config_folder_name 获取配置文件夹路径
    * @return QString 配置文件夹路径，空值表示没有设置
    */
    QString GetConfigFolderPath() const;

    /**
    * @brief WriteJsonToFile 将QJsonDocument对象写入指定位置，如果文件不存在就创建一个json文件
    * @param file_path 目标文件位置，json_doc QJsonDocument对象
    * @return true表示写入成功，false表示写入失败
    */
    bool WriteJsonToFile(const QString file_path, const QJsonDocument& json_doc);

    /**
    * @brief ReadJsonFromFile 以UTF-8格式读取指定位置json文件，返回读取的json数据
    * @param file_path 文件路径
    * @return QJsonDocument 读取到的QJsonDocument对象，空值表示读取失败或者空文件
    */
    QJsonDocument ReadJsonFromFile(const QString file_path) const;

private:
    QString m_config_folder_path;
};

#endif // COMMONFILEPROCESSOR_H
