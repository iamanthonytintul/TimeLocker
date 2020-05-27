
#ifndef BACKENDSERVICE_CONTENT_H
#define BACKENDSERVICE_CONTENT_H
#include <cppcms/form.h>
#include <cppcms/view.h>

namespace content{
    struct info_form : public cppcms::form{
        cppcms::widgets::password input_pass;
        cppcms::widgets::numeric<int> amountOfDays;
        cppcms::widgets::file input_file;
        cppcms::widgets::submit input_submit;
        info_form();
    };

    struct get_form : public cppcms::form{
        cppcms::widgets::text input_key;
        cppcms::widgets::password input_pass;
        cppcms::widgets::submit input_submit;
        get_form();
    };

    struct pass_form: public cppcms::form{
        cppcms::widgets::password input_pass;
        cppcms::widgets::submit pass_submit;
        pass_form();
    };
    struct message: public cppcms::base_content{
        std::string link;
        std::string pass;
    };

    struct upload : public cppcms::base_content{
        info_form info;
    };

    struct get_file : public cppcms::base_content{
        get_form info;
    };

    struct getViaKeyFile : public cppcms::base_content{
        pass_form info;
    };
}

#endif //BACKENDSERVICE_CONTENT_H
