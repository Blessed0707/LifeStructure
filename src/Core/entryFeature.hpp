#pragma once
#include "feature.hpp"
#include "table.hpp"
#include <string>
#include <vector>

/*
    EntryFeature<T>
    A screen that edits and lists a table of entries.

    GoalContainer and JournalContainer were the same screen twice: a title, an
    editor, a save button, a scrolling list, a delete box and a back button.
    Only four things actually differed between them, so those four became
    virtual functions and everything else lives here once.

    This is the Template Method pattern: render() below owns the order of the
    steps, and calls into the derived class for the steps that vary. Compare it
    with Feature, which is a pure interface -- it declares everything and
    implements nothing. Both are inheritance, used for different reasons:

        Feature       -- "GuiApp needs to hold you without knowing what you are"
        EntryFeature  -- "you and your sibling share a body, not just a shape"

    A derived class supplies the four hooks under "the parts that differ" and
    gets the rest for free.
*/
template <typename T>
class EntryFeature : public Feature
{
public:
    explicit EntryFeature(Table<T>& store) : storage(store) {}

    //Refills the in-memory list from the database.
    bool loadStorage() override { return storage.load(entryContainer); }

    //The fixed skeleton. Derived classes do not override this.
    bool render() override;

    const std::vector<T>& getEntryCon() const { return entryContainer; }
    int getEntryConSize() const { return static_cast<int>(entryContainer.size()); }

protected:
    // ---- the parts that differ per feature ----

    //Draws the input widgets. The shared content box lives in contentBuffer;
    //anything else (a name field, mood buttons) is the derived class's own.
    virtual void drawEditor() = 0;

    //Builds an entry from whatever drawEditor() collected. id stays 0 --
    //saveEntry() fills in the real one.
    virtual T buildEntry() const = 0;

    //Resets the input widgets after a successful save.
    virtual void clearEditor() = 0;

    //Draws one entry in the list. The id line is already drawn by render().
    virtual void drawEntry(const T& entry) const = 0;

    // ---- wording, with defaults that most features can keep ----
    virtual std::string title() const { return "Welcome To " + name(); }
    virtual std::string subtitle() const { return ""; }
    virtual std::string entryNoun() const { return "Entry"; }

    // ---- shared behaviour ----
    void addEntry(const T& entry) { entryContainer.push_back(entry); }

    //Writes the entry to the database and fills in its real id.
    bool saveEntry(T& entry) { return storage.insert(entry); }

    //Removes an entry from the database and, if that worked, from memory.
    bool deleteEntry(int id);

    //Every entry type has content, so every editor needs this box.
    char contentBuffer[1024] = "";

private:
    std::vector<T> entryContainer;
    Table<T>& storage;

    //GUI state that every one of these screens needs.
    bool showEntries = false;
    bool showDeleteMenu = false;
    int deleteIdInput = 0;

    //Drops the entry with this id from the in-memory list. Ids come from
    //SQLite, so they are matched rather than used as an index.
    bool forgetEntry(int id);
};

template <typename T>
bool EntryFeature<T>::render()
{
    //Title
    ImGui::PushFont(fontTitle);
    ImGui::Text("%s", title().c_str());
    ImGui::PopFont();

    //Subtitle, if this feature has one
    const std::string sub = subtitle();
    if (!sub.empty())
    {
        ImGui::PushFont(fontHeader);
        ImGui::SetWindowFontScale(.75f);
        ImGui::Text("%s", sub.c_str());
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Spacing();

    //Input widgets
    ImGui::PushFont(fontBody);
    drawEditor();
    ImGui::PopFont();
    ImGui::Separator();

    if (ImGui::Button("Save Entry"))
    {
        //buildEntry() returns a finished value, so nothing is ever read from a
        //half-constructed object. Saved before it is stored in memory, because
        //saveEntry() is what assigns the id.
        T entry = buildEntry();
        if (saveEntry(entry))
        {
            addEntry(entry);
            clearEditor();
        }
    }

    //show entries button that flips to either show or hide when clicked
    if (ImGui::Button(showEntries ? "Hide Entries" : "View Entries"))
    {
        showEntries = !showEntries;
    }

    if (showEntries)
    {
        ImGui::Text("%s", name().c_str());
        ImGui::Separator();

        ImGui::BeginChild("EntryList", ImVec2(0, 300), true); // 0 width = fill available, 300px tall, true = draw a border

        for (const T& entry : entryContainer)
        {
            //entry.id is the database id, so it is shown as-is and can be typed
            //straight into the delete box below.
            ImGui::Text("%s #%d", entryNoun().c_str(), entry.id);
            drawEntry(entry);
            ImGui::Separator();
        }

        ImGui::EndChild();
    }

    if (ImGui::Button("Delete Entry"))
    {
        showDeleteMenu = !showDeleteMenu;
    }

    if (showDeleteMenu)
    {
        ImGui::Text("Enter the ID of the %s to delete:", entryNoun().c_str());
        ImGui::InputInt("ID", &deleteIdInput);

        if (ImGui::Button("Confirm Delete"))
        {
            deleteEntry(deleteIdInput);
            showDeleteMenu = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            showDeleteMenu = false;
        }
    }

    //space before back
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 50.0f));

    if (ImGui::Button("Back"))
    {
        return true; // tell GuiApp the user wants to leave this screen
    }

    return false; // stay on this screen
}

template <typename T>
bool EntryFeature<T>::deleteEntry(int id)
{
    //The database is the source of truth: only drop it from memory if the row
    //was really removed.
    if (!storage.deleteById(id))
    {
        return false;
    }
    forgetEntry(id);
    return true;
}

template <typename T>
bool EntryFeature<T>::forgetEntry(int id)
{
    for (auto it = entryContainer.begin(); it != entryContainer.end(); ++it)
    {
        if (it->id == id)
        {
            entryContainer.erase(it);
            return true;
        }
    }
    return false;
}
