/* Make sure you already have drogon installed in your environment */

/*
  This is a template example from a web app I made that demonstrates an example of 
  a model (User model) as should be used in the 'drogon' web framework
*/

#pragma once

#define USE_MYSQL

#include <drogon/orm/BaseBuilder.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/SqlBinder.h>
#include <json/json.h>
#include <memory>
#include <string>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <vector>


class User {
   public:
    struct Columns {
        std::string username_;
        std::string password_;
        std::string email_;
        uint16_t    id_;
        std::string date_;
    };

    const static std::string primaryKeyName;
    const static int         primaryKeyNumber;
    const static std::string tableName;
    const static bool        hasPrimaryKey;
    using PrimaryKeyType = uint16_t;
    const PrimaryKeyType& getPrimaryKey() const;

    User() { LOG_DEBUG << "User construction!"; }

    User(const drogon::orm::Row& row);

    const uint16_t get_id_val() const noexcept;

    const std::shared_ptr<uint16_t>& get_id() const noexcept;

    const std::string get_username_val() const noexcept;

    const std::shared_ptr<std::string>& get_username() const noexcept;

    const std::string get_password_val() const noexcept;

    const std::shared_ptr<std::string>& get_password() const noexcept;

    const std::string get_email_val() const noexcept;

    const std::shared_ptr<std::string>& get_email() const noexcept;

    const std::string created_at() const noexcept;

    void set_id(uint16_t __id) noexcept;

    void set_username(const std::string& __username) noexcept;

    void set_password(const std::string& __password) noexcept;

    void set_email(const std::string& __email) noexcept;

    void set_created_at(const trantor::Date& __date) noexcept;

    Json::Value to_json() const;

    // for some lower level shit
    std::string        sqlForInserting(bool needSelection = false) const;
    void               updateId(const PrimaryKeyType& newId);
    static std::string sqlForFindingByPrimaryKey() noexcept;
    std::string join(const std::vector<std::string>& elements, const std::string& separator) const;

    friend drogon::orm::Mapper<User>;
    friend drogon::orm::BaseBuilder<User, true, true>;
    friend drogon::orm::BaseBuilder<User, true, false>;
    friend drogon::orm::BaseBuilder<User, false, true>;
    friend drogon::orm::BaseBuilder<User, false, false>;

    static const std::vector<std::string>& insert_columns() noexcept;
    void                           outputArgs(drogon::orm::internal::SqlBinder& binder) const;
    const std::vector<std::string> update_columns() const;
    const std::string              get_column_name(int index) const;

   private:
    std::shared_ptr<uint16_t>    id_;
    std::shared_ptr<std::string> username_;
    std::shared_ptr<std::string> password_;
    std::shared_ptr<std::string> email_;
    std::shared_ptr<std::string> date_;

   public:
    struct MetaData {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t     colLength_;
        const bool        isAutoVal_;
        const bool        isPrimaryKey_;
        const bool        notNull_;
    };

    static const std::vector<MetaData> metaData_;
    bool                               dirtyFlag_[5] = {false};
};


User::User(const drogon::orm::Row& row) {
    if (!row["id"].isNull())
    {
        id_ = std::make_shared<uint16_t>(row["id"].as<uint16_t>());
    }

    if (!row["username"].isNull())
    {
        username_ = std::make_shared<std::string>(row["username"].as<std::string>());
    }

    if (!row["email"].isNull())
    {
        email_ = std::make_shared<std::string>(row["email"].as<std::string>());
    }

    if (!row["password"].isNull())
    {
        password_ = std::make_shared<std::string>(row["password"].as<std::string>());
    }
}

const User::PrimaryKeyType& User::getPrimaryKey() const { return *id_; }

const uint16_t User::get_id_val() const noexcept { return id_ ? *id_ : uint16_t(); }

const std::shared_ptr<uint16_t>& User::get_id() const noexcept { return id_; }

const std::string User::get_username_val() const noexcept {
    return username_ ? *username_ : std::string();
}

const std::shared_ptr<std::string>& User::get_username() const noexcept { return username_; }

const std::string User::get_password_val() const noexcept {
    return password_ ? *password_ : std::string();
}

const std::shared_ptr<std::string>& User::get_password() const noexcept { return password_; }

const std::string User::get_email_val() const noexcept { return email_ ? *email_ : std::string(); }

const std::shared_ptr<std::string>& User::get_email() const noexcept { return email_; }

const std::string User::created_at() const noexcept { return date_ ? *date_ : std::string(); }

/*---setters---*/
void User::set_id(uint16_t __id) noexcept {
    dirtyFlag_[0] = true;
    id_           = std::make_shared<uint16_t>(__id);
}

void User::set_username(const std::string& __username) noexcept {
    dirtyFlag_[1] = true;
    username_     = std::make_shared<std::string>(__username);
}

void User::set_password(const std::string& __password) noexcept {
    dirtyFlag_[2] = true;
    password_     = std::make_shared<std::string>(__password);
}

void User::set_email(const std::string& __email) noexcept {
    dirtyFlag_[3] = true;
    email_        = std::make_shared<std::string>(__email);
}

void User::set_created_at(const trantor::Date& __date) noexcept {
    dirtyFlag_[4] = true;
    // convert to stirng
}

/*---Jsonify---*/

Json::Value User::to_json() const {
    Json::Value js;

    js["id"]       = id_ ? *id_ : uint16_t();
    js["username"] = username_ ? *username_ : std::string();
    js["email"]    = email_ ? *email_ : std::string();
    js["password"] = password_ ? *password_ : std::string();
    js["date"]     = date_ ? *date_ : std::string();

    return js;
}

/*---methods---*/

const std::vector<std::string>& User::insert_columns() noexcept {
    static const std::vector<std::string> cols = {"id", "username", "email", "password", "date"};

    return cols;
}

std::string User::join(const std::vector<std::string>& elements,
                       const std::string&              separator) const {
    std::string result;
    for (size_t i = 0; i < elements.size(); ++i)
    {
        result += elements[i];
        if (i != elements.size() - 1)
            result += separator;
    }
    return result;
}

std::string User::sqlForFindingByPrimaryKey() noexcept {
    return "SELECT * FROM " + tableName + " WHERE " + primaryKeyName + " = ?";
}

std::string User::sqlForInserting(bool needSelection) const {
    std::string              sql = "INSERT INTO " + tableName + " (";
    std::vector<std::string> columns;
    std::vector<std::string> values;

    if (username_)
    {
        columns.emplace_back("username");
        values.emplace_back("?");
    }

    if (email_)
    {
        columns.emplace_back("email");
        values.emplace_back("?");
    }

    if (password_)
    {
        columns.emplace_back("password");
        values.emplace_back("?");
    }

    // Join the columns and values
    sql += join(columns, ", ") + ") VALUES (" + join(values, ", ") + ")";

    if (needSelection)
    {
        sql += " RETURNING *";
    }

    return sql;
}

void User::updateId(const PrimaryKeyType& newId) { id_ = std::make_shared<PrimaryKeyType>(newId); }

void User::outputArgs(drogon::orm::internal::SqlBinder& binder) const {
    if (dirtyFlag_[0])
    {
        if (get_id())
        {
            binder << *id_;
        }
    }

    if (dirtyFlag_[1])
    {
        if (get_username())
        {
            binder << *username_;
        }
    }

    if (dirtyFlag_[2])
    {
        if (get_password())
        {
            binder << *password_;
        }
    }

    if (dirtyFlag_[3])
    {
        if (get_email())
        {
            binder << *email_;
        }
    }

    if (dirtyFlag_[4])
    {
        // do some magic
    }
}

const std::string User::get_column_name(int index) const {
    switch (index)
    {
    case 1 :
        return "username";
    case 2 :
        return "password";
    case 3 :
        return "email";
    case 4 :
        return "date";
    }

    return "";
}

const std::vector<std::string> User::update_columns() const {
    std::vector<std::string> ret;
    for (int i = 1; i <= 4; i++)
    {
        if (dirtyFlag_[i])
        {
            ret.push_back(get_column_name(i));
        }
    }

    return ret;
}