#pragma once
#include "SongInfo.h"
#include <functional>
class CSongDataManager
{
public:
    ~CSongDataManager();

    using SongDataMap = std::unordered_map<wstring, SongInfo>;

    static CSongDataManager& GetInstance();
    void SaveSongData(std::wstring path);		//将所有歌曲信息以序列化的方式保存到文件
    void LoadSongData(std::wstring path);			//从文件中以序列化的方式读取所有歌曲信息

    void SetSongDataModified();
    bool IsSongDataModified() const;

    void SaveSongInfo(const SongInfo& song_info);       //将一个歌曲信息保存到m_song_data中

    SongInfo GetSongInfo(const wstring& file_path);
    SongInfo& GetSongInfoRef(const wstring& file_path);     //获取一个歌曲信息的引用（如果不存在不会插入新的记录）
    SongInfo& GetSongInfoRef2(const wstring& file_path);     //获取一个歌曲信息的引用（如果不存在会插入新的记录）

    const SongDataMap& GetSongData();
    bool IsItemExist(const wstring& file_path) const;
    void AddItem(const wstring& file_path, SongInfo song);
    bool RemoveItem(const wstring& file_path);
    int RemoveItemIf(std::function<bool(const SongInfo&)> fun_condition);       //删除符合条件的项目，返回已删除个数

    void ClearPlayTime();       //清除播放时间统计数据
    void ClearLastPlayedTime();     //清除上次播放时间

private:
    CSongDataManager();

    static CSongDataManager m_instance;

private: 
    SongDataMap m_song_data;		//储存所有歌曲信息数据的映射容器，键是每一个音频文件的绝对路径，对象是每一个音频文件的信息
    bool m_song_data_modified{};
};

