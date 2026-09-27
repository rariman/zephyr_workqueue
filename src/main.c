#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(workqueue_sample, LOG_LEVEL_INF);

#define LED0_NODE DT_ALIAS(led0)

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void work_handler(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(work_delayable, work_handler);

void work_handler(struct k_work *work)
{
        gpio_pin_toggle_dt(&led);
        k_work_schedule(&work_delayable, K_MSEC(CONFIG_TIMER_INTERVAL));
        LOG_INF("LED toggled");
}

int main(void)
{
        if (!device_is_ready(led.port)) {
                LOG_ERR("LED device not ready");
                return 0;
        }

        int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

        if (ret) {
                LOG_ERR("Failed to configure LED");
                return 0;
        }

        k_work_schedule(&work_delayable, K_MSEC(CONFIG_TIMER_INTERVAL));

        return 0;
}
