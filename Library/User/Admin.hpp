#pragma once
#include "Client.hpp"

/// \class Admin
/// \brief Represents a library user with administrator privileges.
///
/// The Admin class inherits from Client but initializes the user with
/// elevated privileges (`m_admin = true`). Administrators have the authority
/// to add or remove books and manage other users in the library system.
class Admin : public Client {
public:
    // Deleted default constructor and copying/moving semantics
    Admin() = delete;
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
    Admin(Admin&&) noexcept = delete;
    Admin& operator=(Admin&&) noexcept = delete;

    /// \brief Default virtual destructor.
    ~Admin() override = default;

    /// \brief Constructs a new Admin user.
    /// \param username The account username.
    /// \param password The account password.
    ///
    /// Passes the credentials to the base Client constructor and flags the account as an administrator.
    Admin(std::string username, std::string password);

    /// \brief Deserializes an Admin from an open file stream.
    /// \param file A reference to an open input file stream positioned at the user's data.
    /// \return A dynamically allocated pointer to the newly created Admin.
    ///
    /// \note The caller is responsible for deleting the returned Admin object.
    static Admin* deserialize(std::ifstream& file);
};
