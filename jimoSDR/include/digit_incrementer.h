/// @file digit_incrementer.h
/// @brief Contains the jimo::jxtd::digit_incrementer control
/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include <xtd/xtd>

/// @brief The jimo::jxtd namespace contains control classes that add to the classes contained in the xtd::forms namespace.
namespace jimo::jxtd

{
    /// @brief Displays a single digit that can be incremented or decremented.
    ///
    /// @remark It is unlikely that you would use a digit_incrementer by itself. It was created for use with the
    /// number_display control.
    /// @par Namespace
    /// jimo::jxtd
    /// @par Library
    /// libjxtd
    /// @par Examples
    /// The following code demonstrates the use of the digit_incrementer control.
    /// @include digit_incrementer/src/digit_incrementer.cpp
    class digit_incrementer : public xtd::forms::panel
    {
        public:
            /// @name Constructors

            /// @brief Initialize a new instance of digit_incrementer.
            digit_incrementer();
            /// @brief Initialize a new instance of digit_incrementer.
            /// @param parent The parent control on the digit_incrementer.
            digit_incrementer(xtd::forms::control& parent);
            /// @brief Initializa a new instance of digit_incrementer.
            /// @param value The initial value to display.
            digit_incrementer(int32_t value);
            /// @brief Initialize a new instance of digit_incrementer.
            /// @param parent The parent control on the digit_incrementer.
            /// @param value The initial value to display.
            digit_incrementer(xtd::forms::control& parent, int32_t value);

            digit_incrementer(const digit_incrementer&) = delete;
            digit_incrementer(digit_incrementer&&) = delete;
            digit_incrementer& operator=(const digit_incrementer&) = delete;
            digit_incrementer& operator=(digit_incrementer&&) = delete;
            /// @name Properties

            /// @{
            /// @brief Retrieve the font properties for the digit displayed in the digit_incrementer.
            /// @returns The xtd::drawing::font object describing properties of the font used to display the
            /// digit in the digit_incrementer.
            virtual xtd::drawing::font font() const override;
            /// @}
            /// @{
            /// @brief Set the font family used to display the digit in the digit_incrementer.
            /// @param font The xtd::drawing::font object containing the font parameters.
            /// @remarks The best font for displaying the digit is probably the default font for the control.
            /// Therefore, it is not recommended that you call this property.
            /// @remarks The size of the font is set to the size of the previous font. This is because the size has been
            /// calculated so that the displayed digit fits nicely inside the digit_incrementer.
            /// @returns A reference to the digit_incrementer object. This allows chaining of property calls together.
            virtual digit_incrementer& font(const xtd::drawing::font& font) override;
            /// @}
            /// @{
            /// @brief Get the height of the digit_incrementer object.
            /// @returns The current height of the object in pixels.
            virtual int32_t height() const override;
            /// @brief Set the height of the digit_incrementer object.
            /// @param height The desired height of the object in pixels.
            /// @returns A reference to the digit_incrementer object. This allows chaining of property calls together.
            /// @remark The size of the obejct is adjusted to be between the minimum and maximum sizes for the object.
            /// @remark The width is calculated to be the (height * minimum width) / minimum height.
            virtual digit_incrementer& height(int32_t height) override;
            /// @}
            /// @{
            /// @brief Get the width and height of the digit_incrementer object
            /// @returns An xtd::drawing::size object containing the width and height of the digit_incrementer object.
            virtual xtd::drawing::size size() const override;
            /// @}
            /// @{
            /// @brief Set the width and height of the digit_incrementer object
            /// @param size the xtd::drawing::size object that specifies the desired width and height.
            /// @returns A reference to the digit_incrementer ibject. This allows chaining of property calls together.
            /// @remark The ratio of width to height is maintained in the ratio 11/16. The size is maintained within
            /// the range between minimum_size and maximum_size. These values are set within the digit_incrementer and
            /// are have  different values for each operating system.
            virtual digit_incrementer& size(const xtd::drawing::size& size) override;
            /// @}
            /// @{
            /// @brief Retrieve the character (single digit) that is displayed in the digit_incrementer.
            /// @returns A reference to the character being displayed.
            virtual const xtd::ustring& text() const override;
            /// @}
            /// @{
            /// @brief Set the character displayed in the digit_incrementer object.
            /// @param value The chararcter to be displayed.
            /// @returns A reference to the digit_incrementer object. This allows chaining of property calls together.
            /// @exception xtd::argument_out_of_range_exception if the character is not in the range 0-9.
            virtual digit_incrementer& text(const xtd::ustring& value) override;
            /// @}
            /// @{
            /// @brief Retrieve the displayed digit as an integer.
            /// @returns The displayed digit.
            virtual int32_t value() const noexcept;
            /// @}
            /// @{
            /// @brief Display the specified value
            /// @param new_value The value to display.
            /// @returns Reference to the digit_incrementer object.
            /// @throws xtd::argument_out_of_range exception if new_value is outside the range 0 through 9.
            digit_incrementer& value(int32_t new_value);
            /// @}
            /// @{
            /// @brief Get the width of the digit_incrementer object.
            /// @returns The current width of the object in pixels.
            virtual int32_t width() const override;
            /// @brief Set the width of the digit_incrementer object.
            /// @param width The desired width of the object in pixels.
            /// @returns A reference to the digit_incrementer object. This allows chaining of property calls together.
            /// @remark The size of the object is adjusted to be between the minimum and maximum sizes for the object.
            /// @remark The height is calculated to be the (width * minimum height) / minimum width.
            virtual digit_incrementer& width(int32_t width) override;
            /// @}

            /// @name  Methods

            /// @{
            /// @brief Increment the value in the digit_incrementer object.
            virtual void increment();
            /// @brief Decrement the value in the digit_incrementer object.
            virtual void decrement();
            /// @brief Convert digit_incrementer object to printable string.
            /// @returns String representation of the object.
            virtual xtd::ustring to_string() const noexcept override;
            /// @}

            /// @{
            /// @brief Steam insertion operator for digit_incrementer object.
            /// @param out The std::ostream to output the digit_incrementer to.
            /// @param incrementer The digit_incrementer object to output.
            /// @returns The std:ostream object.
            friend std::ostream& operator <<(std::ostream& out, const digit_incrementer& incrementer);
            /// @}

            /// @name Events

            /// @{
            /// @brief Occurs when the value in the jimo::jxtd::digit_incrementer changes.
            /// @remarks This event is raised if the jimo::jxtd::digit_incrementer::value or text property is changed by either a programmatic
            xtd::event<digit_incrementer, xtd::event_handler> value_changed;
            /// @brief Occurs when the value in the jimo::jxtd::digit_incrementer increments past 9 and is set to 0.
            /// @remarks This event is raised if the value in jimo::jxtd::digit_incrementer increments past 9. It is
            /// set to 0 before this event is raised.
            xtd::event<digit_incrementer, xtd::event_handler> rolled_over;
            /// @brief Occurs when the value in the jimo::jxtd::digit_incrementer decrements past 0.
            /// @remarks This event is raised if the value in jimo::jxtd::digit_incrementer decrements past 0.
            /// The value is reset to 9 before this event is raised.
            xtd::event<digit_incrementer, xtd::event_handler> rolled_under;
            /// @}
        protected:
            /// @brief Changes the font size to better match the size of the digit_incrementer.
            /// @remark This method is called from the static digit_incrementer_size_changed method.
            virtual void change_font_size_to_fit_control();
            /// @brief Handler for size_changed event.
            ///
            /// This is a static method which determines the digit_incrementer object that raised the event 
            /// (sender) and calls that object's change_font_size_to_fit_control method.
            /// @param sender The digit_incrementer that raised the event.
            /// @param e The event_args object that contains data related to the event. This parameter is
            /// not used.
            static void digit_incrementer_size_changed(xtd::object& sender, const xtd::event_args& e);
            /// @{
            /// @brief Highlight either upper or lower half of control based on cursor position.
            /// @param e mouse_event_args object. This object contains the current mouse position.
            virtual void highlight_upper_or_lower(const xtd::forms::mouse_event_args& e);
            /// @}
            /// @brief Increment or decrement value in the digit_incrementer object
            ///
            /// This method is called from the mouse_clicked method (event handler). It calls either
            /// increment() or decrement() depending on whether the cursor was over the top half 
            /// or the bottom half of the digit_incrementer to do the actual incrementation or
            /// decrementation.
            /// @param e The mouse_event_args object associated with the mouse_click event.
            virtual void increment_decrement_based_on_cursor_position(const xtd::forms::mouse_event_args& e);
            /// @brief Handler for mouse_click event.
            ///
            /// This static method processes the mouse_click event for the digit_incrementer object.
            /// It calls increment_decrement_based_on_cursor_position method for the digit_incrementer
            /// object to actually do any necessary processing.
            /// @param sender The label object within the digit_incrementer object that raised the event.
            /// @param e The mouse_event_args object associated with the event.
            static void mouse_clicked(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            /// @{
            /// @brief Handler for mouse_leave event.
            /// @param sender The digit_incrementer object that the cursor has just left.
            /// @param e The event_args object for the event. This is not used.
            static void mouse_left(xtd::object& sender, const xtd::event_args& e);
            /// @}
            /// @brief Handler for mouse_move event.
            ///
            /// This static method deterrmines the digit_incrementer object that raised the event
            /// (sender) and calls that object's highlight_upper_or_lower method.
            /// @param sender The panel within the digit_incrementer that raised the event.
            /// @param e The mouse_event_args object that contains the data for the event.
            static void mouse_moved(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            /// @brief Raises the jimo::jxtd::digit_incrementer::rolled_over event.
            /// @param e An xtd::event_args object associated with the event.
            virtual void on_roll_over(const xtd::event_args& e);
            /// @brief Raises the jimo::jxtd::digit_incrementer::rolled_under event.
            /// @param e An xtd::event_args object associated with the event.
            virtual void on_roll_under(const xtd::event_args& e);
            /// @brief Raises the jimo::jxtd::digit_incrementer::value_changed event.
            /// @param e An xtd::event_args object associated with the event.
            virtual void on_value_changed(const xtd::event_args& e);
            /// @brief Remove highlight of upper and lower panels
            /// 
            /// This method is called when the mouse cursor leaves the digit_incrementer object.
            virtual void remove_highlight();
            /// @brief Change sizes of upper and lower panels of control whenever its size changes.
            virtual void update_upper_lower_panels() noexcept;
        private:
            xtd::forms::label digit_;
            xtd::forms::panel upper_panel_;
            xtd::forms::panel lower_panel_;
            xtd::drawing::size old_size_;
    };
}